#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Rendering/Shader.h"
#include "../Rendering/Mesh.h"

#include <string>

class Model
{
public:
	Model(void);
	virtual void Init(const char *meshPath);
	virtual void Update();
	virtual void Render(Shader *shader);
	void LoadMeshes(const char *meshPath);
	glm::mat4 GetModelMatrix() { return modelMatrix; };
	void SetTranslation(glm::vec3 translation) { this->translation = translation; }
	void SetScale(glm::vec3 scale) { this->scale = scale; }
	void SetOrientation(glm::quat orientation) { this->orientation = orientation; };
	~Model(void);
protected:
	std::vector<Mesh> meshes;
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::quat orientation;
	glm::mat4 modelMatrix;
	float minX, maxX, minY, maxY, minZ, maxZ;
private:
	
};

