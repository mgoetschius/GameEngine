#include "Mesh.h"
#include <iostream>
#include "../Core/ResourceManager.h"

Mesh::Mesh(void)
{
}

void Mesh::Init(const char *filepath)
{
}

void Mesh::Init(std::vector<Vertex> vertices, unsigned int *indexData, int numVerts, const char *textureName)
{
	numVertices = numVerts;
	float *vertexData = new float[8 * numVertices];

	unsigned int j = 0;
    for(unsigned int i = 0; j < vertices.size(); i+=8)
    {
        vertexData[i] = vertices[j].GetPosition().x;
        vertexData[i+1] = vertices[j].GetPosition().y;
        vertexData[i+2] = vertices[j].GetPosition().z;
        vertexData[i+3] = vertices[j].GetTexCoord().x;
        vertexData[i+4] = vertices[j].GetTexCoord().y;
        vertexData[i+5] = vertices[j].GetNormal().x;
        vertexData[i+6] = vertices[j].GetNormal().y;
        vertexData[i+7] = vertices[j].GetNormal().z;
        j++;
    }

	Init(vertexData, numVertices*8*sizeof(float), indexData, numVertices *sizeof(unsigned int));

	delete [] vertexData;

	std::string basePath = "./res/Textures/";
	std::string texturePath = basePath + textureName;

	texture = ResourceManager::LoadTexture(texturePath.c_str());

}

void Mesh::Init(float *vertexData, unsigned int vertexDataSize, unsigned int *indexData, unsigned int indexDataSize)
{

    glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)12);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void*)20);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBindVertexArray(0);

	glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}

void Mesh::Update()
{

}

void Mesh::Render()
{
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->GetTexture());
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, 0);

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


Mesh::~Mesh(void)
{
	
}
