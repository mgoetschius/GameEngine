#pragma once
#include "glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Shader.h"

#include <memory>

class Billboard
{
public:
	Billboard(void);
	void Init(const char *texturePath);
	void Update();
	void Render(glm::mat4 &view, glm::mat4 &projection);
	~Billboard(void);
private:
	GLuint vao, vbo, ibo;
	Shader shader;
	std::shared_ptr<Texture> texture;

	glm::mat4 modelMatrix;
	glm::vec3 translation, rotation, scale;
};

