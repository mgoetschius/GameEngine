#include "DebugDrawTest.h"


DebugDrawTest::DebugDrawTest(void)
{
	dt = 0;
	lastTime = glfwGetTime();
}

void DebugDrawTest::Init()
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
	shader.UpdateUniform("directionalLight.direction", glm::vec3(1.0f, 0.75f, 0.5f));
	shader.UpdateUniform("directionalLight.intensity", glm::vec3(0.6f));
	shader.UpdateUniform("directionalLight.ambient", glm::vec3(0.2f));

	camera.Init(45.0f, GameEngine::windowWidth, GameEngine::windowHeight, 0.1f, 1000.0f);
	camera.SetCameraPosition(glm::vec3(0, 2.0, 8.0));
	camera.Update();

	physicsWorld.Init();
	physicsWorld.SetDoDebugDraw(true);
	
	std::shared_ptr<PhysicsModel> pPm(new PhysicsModel());
	pPm->SetScale(glm::vec3(1.0f));
	pPm->SetTranslation(glm::vec3(2.1, 0,0));
	pPm->Init("./res/Models/redbox.dae", &physicsWorld, 0.0);
	pPm->Update();
	physicsModels.push_back(std::move(pPm));

	std::shared_ptr<PhysicsModel> pm(new PhysicsModel());
	pm->SetScale(glm::vec3(1.0f));
	pm->SetTranslation(glm::vec3(1.01, 10,0));
	pm->Init("./res/Models/redbox.dae", &physicsWorld, 1.0);
	pm->Update();
	physicsModels.push_back(std::move(pm));

}

void DebugDrawTest::Update(SceneManager *manager, double delta)
{
	camera.Update();
	
	for(std::shared_ptr<Model> pm : physicsModels)
		pm->Update();

	thisTime = glfwGetTime();
	dt = thisTime - lastTime;
	lastTime = thisTime;

	physicsWorld.Update((float)dt, camera.getProjectionMatrix() * camera.getViewMatrix());

	manager->ChangeScene();
		
}

void DebugDrawTest::Render()
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
	

	physicsWorld.Render(camera.getProjectionMatrix() * camera.getViewMatrix());
}


DebugDrawTest::~DebugDrawTest(void)
{
}
