#include "TriMeshScene.h"


TriMeshScene::TriMeshScene(void)
{
	dt = 0;
	lastTime = glfwGetTime();
}

void TriMeshScene::Init()
{
	shader.AddShader(GL_VERTEX_SHADER, "./res/Shaders/vertex.vs");
	shader.AddShader(GL_FRAGMENT_SHADER, "./res/Shaders/fragment.fs");
	shader.CreateProgram();
	shader.Bind();
	shader.AddUniform("mvMatrix");
	shader.AddUniform("pMatrix");
	shader.AddUniform("vMatrix");
	shader.AddUniform("directionalLight.direction");
	shader.AddUniform("directionalLight.intensity");
	shader.AddUniform("directionalLight.ambient");
	shader.UpdateUniform("directionalLight.direction", glm::vec3(1.0f, 0.5f, 0.5f));
	shader.UpdateUniform("directionalLight.intensity", glm::vec3(0.6f));
	shader.UpdateUniform("directionalLight.ambient", glm::vec3(0.2f));

	camera.Init(45.0f, GameEngine::windowWidth, GameEngine::windowHeight, 0.1f, 1000.0f);
	camera.SetCameraPosition(glm::vec3(0.0f, 5.0f, 20.0f));

	physicsWorld.Init();
	physicsWorld.SetDoDebugDraw(true);
	
	std::shared_ptr<PhysicsModelTriMesh> pm(new PhysicsModelTriMesh());
	//pm->SetScale(glm::vec3(20, 0.01, 20));
	pm->Init("./res/Models/ramp.dae", &physicsWorld);
	models.push_back(std::move(pm));
	
	std::shared_ptr<PhysicsModel> ball(new PhysicsModelSphere());
	ball->SetTranslation(glm::vec3(0.0, 12.0, -8.0));
	ball->Init("./res/Models/redsphere.dae", &physicsWorld, 45.0);
	models.push_back(std::move(ball));
	
	std::shared_ptr<Player> player(new Player());
	player->SetTranslation(glm::vec3(4.0, 2.0, 0.0));
	player->Init("./res/Models/player.dae", &physicsWorld, 65.0);
	models.push_back(std::move(player));
	
}

void TriMeshScene::Update(SceneManager *manager, double delta)
{
	camera.Update();
	for(std::shared_ptr<Model> pm : models)
		pm->Update();

	thisTime = glfwGetTime();
	dt = thisTime - lastTime;
	lastTime = thisTime;

	physicsWorld.Update((float)dt, camera.getProjectionMatrix() * camera.getViewMatrix());

	manager->ChangeScene();
}

void TriMeshScene::Render()
{
	shader.Bind();
	glm::mat4 p = camera.getProjectionMatrix();
	glm::mat4 v = camera.getViewMatrix();
	
	shader.UpdateUniform("pMatrix", p);
	shader.UpdateUniform("vMatrix", v);
	
	for(std::shared_ptr<Model> pm : models)
	{
		glm::mat4 mv = camera.getViewMatrix() * pm->GetModelMatrix();
		shader.UpdateUniform("mvMatrix", mv);
		pm->Render(&shader);
	}

	//physicsWorld.Render(p*v);
}


TriMeshScene::~TriMeshScene(void)
{
}
