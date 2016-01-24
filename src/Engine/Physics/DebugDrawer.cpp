#include "DebugDrawer.h"
#include <iostream>


DebugDrawer::DebugDrawer(void)
{
	m_debugMode = DBG_DrawWireframe;

	shader.AddShader(GL_VERTEX_SHADER, "./res/Shaders/debugvertex.vs");
	shader.AddShader(GL_FRAGMENT_SHADER, "./res/Shaders/debugfragment.fs");
	shader.CreateProgram();
	shader.Bind();
	shader.AddUniform("vpMatrix");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	//glBindVertexArray(0);
}

void DebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{
	 vec3 f(from);
	 vec3 t(to);

	 linePoints.push_back(f);
	 linePoints.push_back(t);
}

void DebugDrawer::Render(const glm::mat4 &vpMatrix)
{
	/*
	for(unsigned int i = 0; i < linePoints.size(); i++)
	{
		std::cout << i << ": " << linePoints[i].x << " " << linePoints[i].y << " " << linePoints[i].z << std::endl;
	}
	std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
	*/
	

	//float points [] = { 0, 0, 0, 0, 10, 0 };
	shader.Bind();
	shader.UpdateUniform("vpMatrix", vpMatrix);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, linePoints.size()*4*3, &linePoints[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);

	glDrawArrays(GL_LINES, 0, linePoints.size());

    glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	

	/*
	float vertexData[] = {-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0};
	short indexData[] = {0, 1, 2};
	shader.Bind();
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (GLvoid*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);

    glDisableVertexAttribArray(0);
	*/
	
}

void DebugDrawer::Flush()
{
	linePoints.clear();
}

void DebugDrawer::setDebugMode(int debugMode)
{
    m_debugMode = debugMode;
}


DebugDrawer::~DebugDrawer(void)
{
}

void DebugDrawer::draw3dText(const btVector3& location,const char* textString)
{
}

void DebugDrawer::reportErrorWarning(const char* warningString)
{
}

void DebugDrawer::drawContactPoint(const btVector3& pointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
{
}

