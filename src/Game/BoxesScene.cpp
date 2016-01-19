#include "BoxesScene.h"


BoxesScene::BoxesScene(void)
{
	dt = 0;
	lastTime = glfwGetTime();
}

void BoxesScene::Init()
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
	camera.SetCameraPosition(glm::vec3(0, 10.0, 40));

	physicsWorld.Init();
	
	std::shared_ptr<PhysicsModel> pPm(new PhysicsModel());
	pPm->SetScale(glm::vec3(100, 0.0, 100));
	pPm->Init("./res/Models/greenbox.dae", &physicsWorld, 0.0);
	physicsModels.push_back(std::move(pPm));

	for(int i = 0; i<50; i++)
	{
	std::shared_ptr<PhysicsModel> pPm2(new PhysicsModel());
	float temp = 1.0;
	if(i%2)
		temp *= -1.0;
	pPm2->SetTranslation(glm::vec3(1.8*temp, i*5, -5));
	pPm2->Init("./res/Models/redbox.dae", &physicsWorld, 1.0);
	physicsModels.push_back(std::move(pPm2));
	}
	
}

void BoxesScene::Update(SceneManager *manager, double delta)
{
	camera.Update();
	
	for(std::shared_ptr<Model> pm : physicsModels)
		pm->Update();

	thisTime = glfwGetTime();
	dt = thisTime - lastTime;
	lastTime = thisTime;

	physicsWorld.Update(dt);

	manager->ChangeScene();
		
}

void BoxesScene::Render()
{
	shader.Bind();
	glm::mat4 p = camera.getProjectionMatrix();
	glm::mat4 v = camera.getViewMatrix();
	
	shader.UpdateUniform("pMatrix", p);
	shader.UpdateUniform("vMatrix", v);
	
	for(std::shared_ptr<Model> pm : physicsModels)
	{
		glm::mat4 mv = camera.getViewMatrix() * pm->GetModelMatrix();
		shader.UpdateUniform("mvMatrix", mv);
		pm->Render(&shader);
	}
}


BoxesScene::~BoxesScene(void)
{
	
}
