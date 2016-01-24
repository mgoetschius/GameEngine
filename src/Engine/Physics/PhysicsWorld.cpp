#include "PhysicsWorld.h"
#include <iostream>


PhysicsWorld::PhysicsWorld(void)
{
	
	collisionConfiguration = 0;
	dispatcher = 0;
	broadphaseInterface = 0;
	solver = 0;
	dynamicsWorld = 0;
	
	doDebugDraw = false;
}

void PhysicsWorld::Init()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	broadphaseInterface = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphaseInterface, solver, collisionConfiguration);

	gravity = btVector3(0, -10, 0);

	dynamicsWorld->setGravity(gravity);

	debugDrawer = new DebugDrawer();
	dynamicsWorld->setDebugDrawer(debugDrawer);
}

void PhysicsWorld::Update(const float delta, const glm::mat4 &vpMatrix)
{
	dynamicsWorld->stepSimulation(delta, 10);
	//if(doDebugDraw)
		//dynamicsWorld->debugDrawWorld();
	//debugDrawer->Render(vpMatrix);
	//debugDrawer->Flush();
}

void PhysicsWorld::Render(const glm::mat4 &vpMatrix)
{
	if(doDebugDraw)
		dynamicsWorld->debugDrawWorld();
	debugDrawer->Render(vpMatrix);
	debugDrawer->Flush();
}

void PhysicsWorld::AddCollisionShape(btCollisionShape *shape)
{
	collisionShapes.push_back(shape);
}

void PhysicsWorld::AddBody(btRigidBody *body)
{
	dynamicsWorld->addRigidBody(body);
}


PhysicsWorld::~PhysicsWorld(void)
{
	if(dynamicsWorld)
	{
		for(int i=dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody *body = btRigidBody::upcast(obj);
			if(body && body->getMotionState())
				delete body->getMotionState();
			dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}
	}

	for(int j = 0; j < collisionShapes.size(); j++)
	{
		btCollisionShape *shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

	delete dynamicsWorld;
	delete solver;
	delete broadphaseInterface;
	delete dispatcher;
	delete collisionConfiguration;

	collisionShapes.clear();

	delete debugDrawer;
}
