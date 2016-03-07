#pragma once
#include "PhysicsModel.h"
#include "../Core/Input.h"
class PhysicsModelSphere :
	public PhysicsModel
{
public:
	PhysicsModelSphere(void);
	void Init(const char *meshPath, PhysicsWorld *physicsWorld, float mass);
	void Update();
	~PhysicsModelSphere(void);
};

