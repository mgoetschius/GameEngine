#ifndef VERTEX_H
#define VERTEX_H

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

const int NUM_JOINTS = 4;

class Vertex
{
    public:
        Vertex();
        Vertex(glm::vec3 pos);
        Vertex(glm::vec3 pos, glm::vec2 tex);
        Vertex(glm::vec3 pos, glm::vec2 tex, glm::vec3 norm);
        Vertex(glm::vec3 pos, glm::vec2 tex, glm::vec3 norm, int *jIndices, float *jWeights);
        virtual ~Vertex();
        glm::vec3 GetPosition() { return position; }
        glm::vec3 GetNormal() { return normal; }
        glm::vec2 GetTexCoord() { return texCoord; }
        int* GetJointIndices() { return &jointIndices[0]; }
        float* GetJointWeights() { return &jointWeights[0]; }
    protected:
    private:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
        int jointIndices[NUM_JOINTS];
        float jointWeights[NUM_JOINTS];
};

#endif // VERTEX_H
