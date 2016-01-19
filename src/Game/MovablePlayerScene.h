#pragma once
#include "../Engine/Core/Scene.h"
#include "../Engine/Rendering/Shader.h"
#include "../Engine/Core/Model.h"
#include "../Engine/Rendering/Camera.h"
#include "../Engine/Physics/PhysicsWorld.h"
#include "../Engine/Core/PhysicsModel.h"

#include <vector>
#include <memory>

class MovablePlayerScene :
	public Scene
{
public:
	MovablePlayerScene(void);
	void Init();
	void Update(SceneManager *manager, double delta);
	void Render();
	~MovablePlayerScene(void);
private:
	Shader shader;
	std::vector<std::shared_ptr<Model>> models;
	Camera camera;
	PhysicsWorld physicsWorld;

	double dt, lastTime, thisTime;
};

