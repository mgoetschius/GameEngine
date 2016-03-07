#include "PhysicsModelTriMesh.h"


PhysicsModelTriMesh::PhysicsModelTriMesh(void)
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

void PhysicsModelTriMesh::Init(const char *meshPath, PhysicsWorld *physicsWorld)
{
	LoadMeshes(meshPath);

	this->mass = mass;

	btVector3 size(btScalar(((maxX-minX)/2)*scale.x), btScalar(((maxY-minY)/2)*scale.y), btScalar(((maxZ-minZ)/2)*scale.z));

	btCollisionShape *colShape = new btBvhTriangleMeshShape(triMesh,true);
	physicsWorld->AddCollisionShape(colShape);

	btTransform transform;
	transform.setIdentity();

	btVector3 localInertia(0, 0, 0);
	mass = 0.0;
	bool isDynamic = (mass != 0.0);

	if(isDynamic)
		colShape->calculateLocalInertia(mass, localInertia);

	transform.setOrigin(btVector3(translation.x, translation.y, translation.z));

	motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, colShape, localInertia);
	rbInfo.m_restitution = 1.1;
	body = new btRigidBody(rbInfo);
	physicsWorld->AddBody(body);
	
}

void PhysicsModelTriMesh::LoadMeshes(const char *meshPath)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(meshPath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "Error: " << importer.GetErrorString() << std::endl;
        return;
    }

	aiNode *node = scene->mRootNode;

	for(unsigned int k = 0; k < scene->mNumMeshes; k++)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		aiMesh *mesh = scene->mMeshes[k];

		for(unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			glm::vec3 v;
			v.x = mesh->mVertices[i].x;
			v.y = mesh->mVertices[i].y;
			v.z = mesh->mVertices[i].z;
			glm::vec2 t;
			t.x = mesh->mTextureCoords[0][i].x;
			t.y = mesh->mTextureCoords[0][i].y;
			glm::vec3 n;
			n.x = mesh->mNormals[i].x;
			n.y = mesh->mNormals[i].y;
			n.z = mesh->mNormals[i].z;

			Vertex vertex(v, t, n);
			vertices.push_back(vertex);

			if(v.x < minX)
				minX = v.x;
			if(v.x > maxX)
				maxX = v.x;
			if(v.y < minY)
				minY = v.y;
			if(v.y > maxY)
				maxY = v.y;
			if(v.z < minZ)
				minZ = v.z;
			if(v.z > maxZ)
				maxZ = v.z;
		}
	
		for(unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh ->mFaces[i];
			for(unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		aiString str;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &str);

		std::shared_ptr<Mesh> m(new Mesh());
		m->Init(vertices, &indices[0], indices.size(), str.C_Str());
		meshes.push_back(std::move(m));

		triMesh = new btTriangleMesh();
		for(int i = 0; i < indices.size(); i+=3)
		{
			btVector3 v0(vertices[i].GetPosition().x, vertices[i].GetPosition().y, vertices[i].GetPosition().z);
			btVector3 v1(vertices[i+1].GetPosition().x, vertices[i+1].GetPosition().y, vertices[i+1].GetPosition().z);
			btVector3 v2(vertices[i+2].GetPosition().x, vertices[i+2].GetPosition().y, vertices[i+2].GetPosition().z);

			triMesh->addTriangle(v0, v1, v2);
		}
		std::cout << triMesh->getNumTriangles() << std::endl;
	}
}


PhysicsModelTriMesh::~PhysicsModelTriMesh(void)
{
	delete triMesh;
}
