#pragma once
#include "linearmath\btidebugdraw.h"
#include "btBulletDynamicsCommon.h"
#include <glew.h>

#include "../Rendering/Shader.h"

struct vec3
{
	vec3(const btVector3 &vec)
		:x(vec.x()),
		y(vec.y()),
		z(vec.z())
	{}
	float x;
	float y; 
	float z;
};

class DebugDrawer : 	public btIDebugDraw
{
public:
	DebugDrawer(void);
	virtual void drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color);
	virtual void   drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance,int lifeTime,const btVector3& color);
    virtual void   reportErrorWarning(const char* warningString);

    virtual void   draw3dText(const btVector3& location,const char* textString);
    virtual void   setDebugMode(int debugMode);
    virtual int    getDebugMode() const { return m_debugMode;}
	~DebugDrawer(void);

	void Render(const glm::mat4 &vpMatrix);
	void Flush();
private:
	int m_debugMode;
	btAlignedObjectArray<vec3> linePoints;

	Shader shader;
	GLuint vao, vbo, ibo;
	
};



