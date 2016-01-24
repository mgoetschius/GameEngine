#pragma once
#include<btBulletDynamicsCommon.h>
#include<BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include "DebugDrawer.h"

class PhysicsWorld
{
public:
	PhysicsWorld(void);
	void Init();
	void AddBody(btRigidBody *body);
	void AddCollisionShape(btCollisionShape *shape);
	void Update(const float delta, const glm::mat4 &vpMatrix);
	void Render(const glm::mat4 &vpMatrix);
	~PhysicsWorld(void);
	void SetDoDebugDraw(bool val) { doDebugDraw = val; }
private:
	btDefaultCollisionConfiguration *collisionConfiguration;
	btCollisionDispatcher *dispatcher;
	btBroadphaseInterface *broadphaseInterface;
	btSequentialImpulseConstraintSolver *solver;
	btDiscreteDynamicsWorld *dynamicsWorld;

	btVector3 gravity;

	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	DebugDrawer *debugDrawer;
	bool doDebugDraw;
};

