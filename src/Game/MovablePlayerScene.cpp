#include "MovablePlayerScene.h"


MovablePlayerScene::MovablePlayerScene(void)
{
	dt = 0;
	lastTime = thisTime = glfwGetTime();
}

void MovablePlayerScene::Init()
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

	std::shared_ptr<PhysicsModel> pm(new PhysicsModel());
	pm->SetScale(glm::vec3(10, 0.01, 10));
	pm->Init("./res/Models/greenbox.dae", &physicsWorld, 0.0);
	models.push_back(std::move(pm));

	pm.reset(new PhysicsModel());
	pm->Init("./res/Models/redbox.dae", &physicsWorld, 1.0);
	models.push_back(std::move(pm));

	pm.reset(new PhysicsModel());
	pm->SetTranslation(glm::vec3(-4.0, 0.0, -2.0));
	pm->Init("./res/Models/yellowbox.dae", &physicsWorld, 1.0);
	models.push_back(std::move(pm));
	
	std::shared_ptr<Player> player(new Player());
	player->SetTranslation(glm::vec3(4.0, 10.0, -5.0));
	player->Init("./res/Models/player.dae", &physicsWorld, 65.0);
	models.push_back(std::move(player));
	
}

void MovablePlayerScene::Update(SceneManager *manager, double delta)
{
	camera.Update();
	for(std::shared_ptr<Model> pm : models)
		pm->Update();

	thisTime = glfwGetTime();
	dt = thisTime - lastTime;
	lastTime = thisTime;

	physicsWorld.Update((float)dt);

	manager->ChangeScene();
}

void MovablePlayerScene::Render()
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
}


MovablePlayerScene::~MovablePlayerScene(void)
{
}
