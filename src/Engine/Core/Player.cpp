#include "Player.h"


Player::Player(void)
{
	std::cout << "constructing player\n";
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
	mass = 1.0f;
}

void Player::Init(const char *meshPath, PhysicsWorld *physicsWorld, float mass)
{
	LoadMeshes(meshPath);

	this->mass = mass;

	btVector3 size(btScalar(((maxX-minX)/2)*scale.x), btScalar(((maxY-minY)/2)*scale.y), btScalar(((maxZ-minZ)/2)*scale.z));

	//btCollisionShape *colShape = new btBoxShape(size);
	btCollisionShape *colShape = new btCapsuleShape(size.getX(), size.getY());
	physicsWorld->AddCollisionShape(colShape);

	btTransform transform;
	transform.setIdentity();

	btVector3 localInertia(0, 0, 0);

	bool isDynamic = (mass != 0.0);

	if(isDynamic)
		colShape->calculateLocalInertia(mass, localInertia);

	transform.setOrigin(btVector3(translation.x, translation.y+1.0f, translation.z));

	motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, colShape, localInertia);
	
	body = new btRigidBody(rbInfo);

	body->setFriction(1.75);
	body->setAngularFactor(btVector3(0.0, 0.0, 0.0));
	body->setActivationState(DISABLE_DEACTIVATION);
	

	physicsWorld->AddBody(body);
}

void Player::Update()
{
	//body->applyCentralImpulse(btVector3(0,0,5));
	//body->applyCentralForce(btVector3(0, 0, 525));
	btTransform tran;
	body->getMotionState()->getWorldTransform(tran);
	//std::cout << tran.getOrigin().getZ() << std::endl;

	btVector3 velocity;
	velocity = body->getLinearVelocity();
	
	if(Input::IsDown(Input::KEY_K))
	{
			body->setLinearVelocity(btVector3(velocity.getX(), velocity.getY(), 2.9));
			//body2->applyCentralForce(btVector3(0, 0, 500));
	}
	if(Input::IsDown(Input::KEY_I))
		body->setLinearVelocity(btVector3(velocity.getX(), velocity.getY(), -2.9));
	if(Input::IsDown(Input::KEY_J))
		body->setLinearVelocity(btVector3(-2.9, velocity.getY(), velocity.getZ()));
	if(Input::IsDown(Input::KEY_L))
		body->setLinearVelocity(btVector3(2.9, velocity.getY(), velocity.getZ()));

	if(Input::IsDown(Input::KEY_UP))
		if(velocity.getZ() > -3.0)
			body->applyCentralForce(btVector3(0,0,-1000));
	if(Input::IsDown(Input::KEY_DOWN))
		if(velocity.getZ() < 3.0)
			body->applyCentralForce(btVector3(0,0,1000));
	if(Input::IsDown(Input::KEY_LEFT))
		if(velocity.getX() > -3.0)
			body->applyCentralForce(btVector3(-1000,0,0));
	if(Input::IsDown(Input::KEY_RIGHT))
		if(velocity.getX() < 3.0)
			body->applyCentralForce(btVector3(1000,0,0));
		
	
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


Player::~Player(void)
{
}
