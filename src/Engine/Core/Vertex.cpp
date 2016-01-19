#include "Vertex.h"

Vertex::Vertex()
{
    position = glm::vec3(0.0, 0.0, 0.0);
    texCoord = glm::vec2(0.0, 0.0);
    normal = glm::vec3(0.0, 0.0, 0.0);
    for(int i = 0; i < NUM_JOINTS; i++)
    {
        jointIndices[i] = -1;
        jointWeights[i] = 0.0;
    }
}

Vertex::Vertex(glm::vec3 pos)
{
    position = pos;
    texCoord = glm::vec2(0.0, 0.0);
    normal = glm::vec3(0.0, 0.0, 0.0);
    for(int i = 0; i < NUM_JOINTS; i++)
    {
        jointIndices[i] = -1;
        jointWeights[i] = 0.0;
    }
}

Vertex::Vertex(glm::vec3 pos, glm::vec2 tex)
{
    position = pos;
    texCoord = tex;
    normal = glm::vec3(0.0, 0.0, 0.0);
    for(int i = 0; i < NUM_JOINTS; i++)
    {
        jointIndices[i] = -1;
        jointWeights[i] = 0.0;
    }
}

Vertex::Vertex(glm::vec3 pos, glm::vec2 tex, glm::vec3 norm)
{
    position = pos;
    texCoord = tex;
    normal = norm;
    for(int i = 0; i < NUM_JOINTS; i++)
    {
        jointIndices[i] = -1;
        jointWeights[i] = 0.0;
    }
}

Vertex::Vertex(glm::vec3 pos, glm::vec2 tex, glm::vec3 norm, int *jIndices, float *jWeights)
{
    position = pos;
    texCoord = tex;
    normal = norm;
    for(int i = 0; i < NUM_JOINTS; i++)
    {
        jointIndices[i] = jIndices[i];
        jointWeights[i] = jWeights[i];
    }
}

Vertex::~Vertex()
{
    //dtor
}
