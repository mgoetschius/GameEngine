#pragma once
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	virtual void Init();
	void Update(double delta);
	void Render();
	virtual void ChangeScene();
	~SceneManager();

protected:
	Scene *scene;

private:
	
	
};
