#pragma once
#include "../Engine/Core/Scene.h"
#include "../Engine/Rendering/Shader.h"
#include "../Engine/Core/Model.h"
#include "../Engine/Rendering/Camera.h"
#include "../Engine/Physics/PhysicsWorld.h"
#include "../Engine/Core/PhysicsModel.h"
#include "../Engine/Core/PhysicsModelTriMesh.h"
#include "../Engine/Core/PhysicsModelSphere.h"
#include "../Engine/Core/Player.h"

#include <vector>
#include <memory>

class TriMeshScene :
	public Scene
{
public:
	TriMeshScene(void);
	void Init();
	void Update(SceneManager *manager, double delta);
	void Render();
	~TriMeshScene(void);

	Shader shader;
	std::vector<std::shared_ptr<Model>> models;
	Camera camera;
	PhysicsWorld physicsWorld;

	double dt, lastTime, thisTime;
};

