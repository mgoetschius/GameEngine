#pragma once
#include "../Engine/Core/SceneManager.h"
#include "../Engine/Core/ResourceManager.h"
#include "BaseScene.h"
#include "BoxesScene.h"
#include "MovablePlayerScene.h"
#include "DebugDrawTest.h"

class TestSceneManager :
	public SceneManager
{
public:
	TestSceneManager(void);
	void Init();
	void ChangeScene();
	~TestSceneManager(void);
};

