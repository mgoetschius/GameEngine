#pragma once
#include <map>
#include <memory>
#include "../Rendering/Mesh.h"
#include "../Rendering/Texture.h"
class ResourceManager
{
public:
	ResourceManager(void);
	static Mesh* LoadMesh(const char *filename);
	static std::shared_ptr<Texture> LoadTexture(const char *filename);
	static void ClearTextures();
	static void ClearMeshes();
	~ResourceManager(void);
private:
	static std::map<const char*, Mesh*> meshes;
	static std::map<const char*, std::shared_ptr<Texture>> textures;
};

