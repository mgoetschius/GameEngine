#include "BaseScene.h"
#include <iostream>
#include <math.h>


BaseScene::BaseScene(void)
{
}

void BaseScene::Init()
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
	camera.SetCameraPosition(glm::vec3(0.0, 1.0, -8.0));

	Model m;
	m.Init("./res/Models/groundplane.dae");
	models.push_back(m);
	Model c;
	c.Init("./res/Models/cube.dae");
	c.SetOrientation(glm::quat(1,0,0,0));
	c.SetTranslation(glm::vec3(0, 0, -5));
	c.Update();
	//models.push_back(c);

	billboard.Init("./res/Textures/billboard.png");
	
}

void BaseScene::Update(SceneManager *manager, double delta)
{
	camera.Update();
	for(Model &model : models)
		model.Update();

	manager->ChangeScene();
		
}

void BaseScene::Render()
{
	shader.Bind();
	glm::mat4 p = camera.getProjectionMatrix();
	glm::mat4 v = camera.getViewMatrix();
	
	shader.UpdateUniform("pMatrix", p);
	shader.UpdateUniform("vMatrix", v);

	for(Model &model : models)
	{
		glm::mat4 mv = camera.getViewMatrix() * model.GetModelMatrix();
		shader.UpdateUniform("mvMatrix", mv);
		model.Render(&shader);
	}
	
	billboard.Render(v, p);
	
}


BaseScene::~BaseScene(void)
{
	
}
