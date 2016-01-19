#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;

out vec2 TexCoords;
out vec3 ViewSpaceNormal;
out vec3 ViewSpacePosition;

uniform mat4 mvMatrix;
uniform mat4 pMatrix;

void main()
{
	vec4 tempPosition = (mvMatrix * vec4(position, 1.0));
	gl_Position = pMatrix * tempPosition;;
	
	ViewSpaceNormal = mat3(mvMatrix) * normal;
	ViewSpacePosition = vec3(tempPosition);
	TexCoords = texCoords;
}