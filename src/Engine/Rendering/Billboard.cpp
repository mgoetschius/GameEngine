#include "Billboard.h"
#include "../Core/ResourceManager.h"


Billboard::Billboard(void)
{
}

void Billboard::Init(const char *texturePath)
{
	shader.AddShader(GL_VERTEX_SHADER, "./res/Shaders/billboardvertex.vs");
	shader.AddShader(GL_FRAGMENT_SHADER, "./res/Shaders/billboardfragment.fs");
	shader.CreateProgram();
	shader.AddUniform("mvpMatrix");

	texture = ResourceManager::LoadTexture(texturePath);

	GLfloat vertexData[] = 
		{-0.5, -0.5, 0.0, 0.0, 1.0,
		  0.5, -0.5, 0.0, 1.0, 1.0,
		  0.5, 0.5, 0.0, 1.0, 0.0,
		 -0.5, 0.5, 0.0, 0.0, 0.0
		};

	GLushort indexData[] = {0, 1, 2, 0, 2, 3};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBindVertexArray(0);

	glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

	translation =glm::vec3(0.0, 1.0, -10.0);
	rotation = glm::vec3(1.0);
	scale = glm::vec3(2.0);
	Update();
}

inline float DegToRad(float fAngDeg)
{
	const float fDegToRad = 3.14159f * 2.0f / 360.0f;
	return fAngDeg * fDegToRad;
}

void Billboard::Update()
{
	modelMatrix = glm::mat4(1.0);
    modelMatrix = glm::translate(modelMatrix, translation);
    modelMatrix = glm::rotate(modelMatrix, DegToRad(rotation.x), glm::vec3(1,0,0));
    modelMatrix = glm::rotate(modelMatrix, DegToRad(rotation.y), glm::vec3(0,1,0));
    modelMatrix = glm::rotate(modelMatrix, DegToRad(rotation.z), glm::vec3(0,0,-1));
    modelMatrix = glm::scale(modelMatrix, scale);
}

void Billboard::Render(glm::mat4 &view, glm::mat4 &projection)
{
	glm::mat4 mv = view * modelMatrix;
	mv[0][0] = 1.0;
	mv[0][1] = 0.0;
	mv[0][2] = 0.0;
	
	mv[1][0] = 0.0;
	mv[1][1] = 1.0;
	mv[1][2] = 0.0;
	
	mv[2][0] = 0.0;
	mv[2][1] = 0.0;
	mv[2][2] = 1.0;

	mv = glm::scale(mv, scale);

	shader.Bind();
	shader.UpdateUniform("mvpMatrix", projection * mv);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTexture());
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}


Billboard::~Billboard(void)
{
}
