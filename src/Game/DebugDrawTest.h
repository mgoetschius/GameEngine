#pragma once
#include "../Engine/Core/Scene.h"
#include "../Engine/Rendering/Shader.h"
#include "../Engine/Rendering/Camera.h"
#include "../Engine/Core/Model.h"
#include "../Engine/Core/PhysicsModel.h"
#include "../Engine/Physics/PhysicsWorld.h"

#include <vector>
#include <memory>


class DebugDrawTest :
	public Scene
{
public:
	DebugDrawTest(void);
	void Init();
	void Update(SceneManager *manager, double delta);
	void Render();
	~DebugDrawTest(void);
private:
	Shader shader;
	std::vector<std::shared_ptr<Model>> physicsModels;
	Camera camera;

	PhysicsWorld physicsWorld;

	double dt, lastTime, thisTime;
};

