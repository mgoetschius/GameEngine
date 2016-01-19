#include "SceneManager.h"
#include <iostream>



SceneManager::SceneManager()
{
}

void SceneManager::Init()
{
	
}

void SceneManager::ChangeScene()
{
}

void SceneManager::Update(double delta)
{
	scene->Update(this, delta);
}

void SceneManager::Render()
{
	scene->Render();
}


SceneManager::~SceneManager()
{
	
}
