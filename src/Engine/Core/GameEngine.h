#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "Input.h"
#include "SceneManager.h"

class GameEngine
{
public:
	GameEngine(int width, int height, int fps, SceneManager *manager);
	void Start();
	void Run(GLFWwindow *win);
	void Update(double delta);
	void Render(GLFWwindow *window);
	~GameEngine(void);
	static int windowWidth;
	static int windowHeight;
private:
	int fps;
	SceneManager *sceneManager;
};

