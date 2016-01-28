#include "PhysicsModel.h"


PhysicsModel::PhysicsModel(void)
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
}

void PhysicsModel::Init(const char *meshPath, PhysicsWorld *physicsWorld, float mass)
{
	LoadMeshes(meshPath);

	this->mass = mass;

	btVector3 size(btScalar(((maxX-minX)/2)*scale.x), btScalar(((maxY-minY)/2)*scale.y), btScalar(((maxZ-minZ)/2)*scale.z));

	btCollisionShape *colShape = new btBoxShape(size);
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
	body = new btRigidBody(rbInfo);

	physicsWorld->AddBody(body);
}

void PhysicsModel::Update()
{
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


PhysicsModel::~PhysicsModel(void)
{
}
