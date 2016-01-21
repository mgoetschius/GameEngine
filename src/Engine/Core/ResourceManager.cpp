#include "ResourceManager.h"

std::map<const char*, Mesh*> ResourceManager::meshes;
std::map<const char*, std::shared_ptr<Texture>> ResourceManager::textures;


ResourceManager::ResourceManager(void)
{
}

Mesh* ResourceManager::LoadMesh(const char *filename)
{
	if(meshes.find(filename) != meshes.end())
		return meshes[filename];
	else
	{
		meshes[filename] = new Mesh();
		meshes[filename]->Init(filename);
		return meshes[filename];
	}
}

void ResourceManager::ClearMeshes()
{
    for(std::map<const char*, Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it)
    {
        delete it->second;
    }
    meshes.clear();
}

std::shared_ptr<Texture> ResourceManager::LoadTexture(const char *filename)
{
	if(textures.find(filename) != textures.end())
		return textures[filename];
	else
	{
		textures[filename] = std::shared_ptr<Texture>(new Texture(filename));
		return textures[filename];
	}
}

void ResourceManager::ClearTextures()
{
	textures.clear();
}


ResourceManager::~ResourceManager(void)
{
	ClearMeshes();
}
