#pragma once
#include<btBulletDynamicsCommon.h>
#include<BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

class PhysicsWorld
{
public:
	PhysicsWorld(void);
	void Init();
	void AddBody(btRigidBody *body);
	void AddCollisionShape(btCollisionShape *shape);
	void Update(float delta);
	~PhysicsWorld(void);
private:
	btDefaultCollisionConfiguration *collisionConfiguration;
	btCollisionDispatcher *dispatcher;
	btBroadphaseInterface *broadphaseInterface;
	btSequentialImpulseConstraintSolver *solver;
	btDiscreteDynamicsWorld *dynamicsWorld;

	btVector3 gravity;

	btAlignedObjectArray<btCollisionShape*> collisionShapes;
};

