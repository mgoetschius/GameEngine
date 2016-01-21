#pragma once
#include "glew.h"
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <memory>

#include "../Core/Vertex.h"
#include "Texture.h"

class Mesh
{
public:
	Mesh(void);
	void Init(const char *filepath);
	void Init(std::vector<Vertex> vertices, unsigned int *indexData, int numVerts, const char *textureName);
	void Init(float*, unsigned int, unsigned int*, unsigned int);
	void Update();
	void Render();
	~Mesh(void);
private:
	GLuint vao, vbo, ibo;
	std::shared_ptr<Texture> texture;
	unsigned int numVertices;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

