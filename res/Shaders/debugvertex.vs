#version 330

layout(location = 0) in vec3 position;

out vec4 Color;

uniform mat4 vpMatrix;

void main()
{
	gl_Position = vpMatrix * vec4(position, 1.0);
	
	Color = vec4(0.0, 1.0, 0.0, 1.0);
}