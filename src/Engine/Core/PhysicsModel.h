#pragma once
#include "model.h"
#include <btBulletDynamicsCommon.h>
#include "../Physics/PhysicsWorld.h"
class PhysicsModel :
	public Model
{
public:
	PhysicsModel(void);
	void Init(const char *meshPath, PhysicsWorld *physicsWorld, float mass);
	void Update();
	~PhysicsModel(void);
protected:
	btScalar mass;
	btDefaultMotionState *motionState;
	btRigidBody *body;
	btTransform trans;
};

