#pragma once
#include "Model.h"
#include "PhysicsModel.h"
#include "../Core/Input.h"
#include <btBulletDynamicsCommon.h>
#include "../Physics/PhysicsWorld.h"
class Player : public PhysicsModel
{
public:
	Player(void);
	void Init(const char *meshPath, PhysicsWorld *physicsWorld, float mass);
	void Update();
	void Render(Shader &shader);
	~Player(void);
private:
	btScalar mass;
	btDefaultMotionState *motionState;
};

