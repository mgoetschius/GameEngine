#version 330

in vec2 TexCoords;
in vec3 ViewSpaceNormal;
in vec3 ViewSpacePosition;

struct DirectionalLight
{
	vec3 direction;
	vec3 intensity;
	vec3 ambient;
};

uniform sampler2D Texture;
uniform mat4 vMatrix;
uniform DirectionalLight directionalLight;

out vec4 outputColor;

vec4 CalculateDirectional()
{
	vec3 dirToLightViewSpace = normalize(mat3(vMatrix) * directionalLight.direction);
	vec3 Normal = normalize(ViewSpaceNormal);
	float cosAngIncidence = dot(Normal, dirToLightViewSpace);
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	return texture(Texture, TexCoords) * directionalLight.intensity * cosAngIncidence + texture(Texture, TexCoords)* vec4(directionalLight.ambient, 1.0);
}

void main()
{
	outputColor = CalculateDirectional();
}