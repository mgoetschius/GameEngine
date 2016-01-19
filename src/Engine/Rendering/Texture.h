#pragma once
#include <glew.h>

class Texture
{
public:
	Texture(const char* filepath);
	GLuint GetTexture() { return texID; }
	~Texture(void);
private:
	int width, height, n;
	GLuint texID;
	GLuint LoadTexture(const char *filepath);
};

