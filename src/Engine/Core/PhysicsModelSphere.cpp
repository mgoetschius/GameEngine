#include "PhysicsModelSphere.h"


PhysicsModelSphere::PhysicsModelSphere(void)
{
	minX = std::numeric_limits<float>::max();
    maxX = std::numeric_limits<float>::min();
    minZ = std::numeric_limits<float>::max();
    maxZ = std::numeric_limits<float>::min();
    minY = std::numeric_limits<float>::max();
    maxY = std::numeric_limits<float>::min();
	translation = glm::vec3(0.0);
	rotation = glm::vec3(0.0);
	scale = glm::vec3(1.0);
	orientation = glm::quat(1,0,0,0);

	motionState = 0;
	body = 0;
}

void PhysicsModelSphere::Init(const char *meshPath, PhysicsWorld *physicsWorld, float mass)
{
	std::cout << "in sphere init\n";
	LoadMeshes(meshPath);
	this->mass = mass;

	btCollisionShape *colShape = new btSphereShape((maxX-minX)/2);
	physicsWorld->AddCollisionShape(colShape);

	btTransform transform;
	transform.setIdentity();

	btVector3 localInertia(0, 0, 0);

	bool isDynamic = (mass != 0.0);

	if(isDynamic)
		colShape->calculateLocalInertia(mass, localInertia);

	transform.setOrigin(btVector3(translation.x, translation.y, translation.z));

	motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, colShape, localInertia);
	rbInfo.m_friction = 0.5;
	rbInfo.m_restitution = 0.5;
	body = new btRigidBody(rbInfo);

	physicsWorld->AddBody(body);
}

void PhysicsModelSphere::Update()
{
	//temp code for testing to be removed
	/*
	if(Input::IsDown(Input::KEY_UP))
			body->applyCentralForce(btVector3(0,0,-1000));
	if(Input::IsDown(Input::KEY_LEFT))
			body->applyCentralForce(btVector3(-500,0,0));
	if(Input::IsDown(Input::KEY_RIGHT))
			body->applyCentralForce(btVector3(500,0,0));
	*/
	//end temp code

	motionState->getWorldTransform(trans);
	translation = glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	orientation = glm::quat(trans.getRotation().getW(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ());

	modelMatrix = glm::mat4(1.0);
	glm::mat4 transform(1.0);
	transform = glm::translate(transform, translation);
	glm::mat4 rot = glm::mat4_cast(orientation);
	glm::mat4 s(1.0);
	s = glm::scale(s, scale);
	modelMatrix = transform * rot * s;
}


PhysicsModelSphere::~PhysicsModelSphere(void)
{
}
