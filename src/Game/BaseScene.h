#pragma once
#include "../Engine/Core/Scene.h"
#include "../Engine/Core/SceneManager.h"
#include "../Engine/Rendering/Shader.h"
#include "../Engine/Core/Model.h"
#include "../Engine/Core/PhysicsModel.h"
#include "../Engine/Rendering/Camera.h"
#include "../Engine/Physics/PhysicsWorld.h"

#include "../Engine/Rendering/Billboard.h"

#include <vector>
#include <memory>

class BaseScene :
	public Scene
{
public:
	BaseScene(void);
	void Init();
	void Update(SceneManager *manager, double delta);
	void Render();
	~BaseScene(void);
private:
	Shader shader;
	std::vector<Model> models;
	Camera camera;

	Billboard billboard;
};

