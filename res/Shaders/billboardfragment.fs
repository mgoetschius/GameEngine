#version 330

in vec4 Color;
in vec2 TexCoords;

out vec4 outputColor;

uniform sampler2D Texture;

void main()
{
	//outputColor = Color;
	outputColor = texture(Texture, TexCoords);
}