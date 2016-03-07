#pragma once
#include "physicsmodel.h"
class PhysicsModelTriMesh :
	public PhysicsModel
{
public:
	PhysicsModelTriMesh(void);
	void Init(const char *meshPath, PhysicsWorld *physicsWorld);
	~PhysicsModelTriMesh(void);
private:
	void LoadMeshes(const char *meshPath);
	btTriangleMesh *triMesh;
};

