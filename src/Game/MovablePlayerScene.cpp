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
	shader.UpdateUniform("directionalLight.direction", glm::vec3(1.0, 0.5, 0.5));
	shader.UpdateUniform("directionalLight.intensity", glm::vec3(0.6));
	shader.UpdateUniform("directionalLight.ambient", glm::vec3(0.2));

	camera.Init(45.0, GameEngine::windowWidth, GameEngine::windowHeight, 0.1, 1000);
	camera.SetCameraPosition(glm::vec3(0, 1.0, 0));

	physicsWorld.Init();

	std::shared_ptr<PhysicsModel> pm(new PhysicsModel);
	pm->SetScale(glm::vec3(10, 0.0, 10));
	pm->Init("./res/Models/greenbox.dae", &physicsWorld, 0.0);
	models.push_back(pm);
}

void MovablePlayerScene::Update(SceneManager *manager, double delta)
{
	camera.Update();
	for(std::shared_ptr<Model> pm : models)
		pm->Update();

	thisTime = glfwGetTime();
	dt = thisTime - lastTime;
	lastTime = thisTime;

	physicsWorld.Update(dt);

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
