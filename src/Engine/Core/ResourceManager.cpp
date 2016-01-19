#include "ResourceManager.h"

std::map<const char*, Mesh*> ResourceManager::meshes;
std::map<const char*, Texture*> ResourceManager::textures;


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

Texture* ResourceManager::LoadTexture(const char *filename)
{
	if(textures.find(filename) != textures.end())
		return textures[filename];
	else
	{
		textures[filename] = new Texture(filename);
		return textures[filename];
	}
}

void ResourceManager::ClearTextures()
{
    for(std::map<const char*, Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
    {
        GLuint id = it->second->GetTexture();
        glDeleteTextures(1, &id);
        delete it->second;
    }
    textures.clear();
}


ResourceManager::~ResourceManager(void)
{
	ClearMeshes();
	ClearTextures();
}
