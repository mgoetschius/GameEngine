#include "TestSceneManager.h"


TestSceneManager::TestSceneManager(void)
{
}

void TestSceneManager::Init()
{
	scene = new BaseScene();
	scene->Init();
}

void TestSceneManager::ChangeScene()
{
	if(Input::IsPressed(Input::KEY_1))
	{
		delete scene;
		scene = new BaseScene();
		scene->Init();
		
	}
	if(Input::IsPressed(Input::KEY_2))
	{
		delete scene;
		scene = new BoxesScene();
		scene->Init();
		
	}
	if(Input::IsPressed(Input::KEY_3))
	{
		delete scene;
		scene = new MovablePlayerScene();
		scene->Init();
		
	}
}


TestSceneManager::~TestSceneManager(void)
{
	delete scene;
}
