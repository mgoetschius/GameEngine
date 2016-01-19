#include "GameEngine.h"

int GameEngine::windowWidth;
int GameEngine::windowHeight;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


GameEngine::GameEngine(int width, int height, int framesPerSec, SceneManager *manager)
{
	windowWidth = width;
	windowHeight = height;
	fps = framesPerSec;
	sceneManager = manager;
}

void GameEngine::Start()
{
	if(!glfwInit())
		return;

	GLFWwindow *window = glfwCreateWindow(GameEngine::windowWidth, GameEngine::windowHeight, "Window", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
    glewInit();

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n\n";

	glViewport(0, 0, GameEngine::windowWidth, GameEngine::windowHeight);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	sceneManager->Init();

	Run(window);

	glfwTerminate();
}

void GameEngine::Run(GLFWwindow *win)
{
	double secPerFrame = 1.0 / fps;
	double lastTime = glfwGetTime();
	double currentTime = lastTime;
	double timer = lastTime;
	double elapsedTime = 0;
	int updates = 0;
	int frames = 0;

	while(!glfwWindowShouldClose(win))
	{
		currentTime = glfwGetTime();
		elapsedTime += currentTime - lastTime;
		lastTime = currentTime;
		while(elapsedTime >= secPerFrame)
		{
			Update(elapsedTime);
			updates++;
			elapsedTime -= secPerFrame;
		}

		Render(win);
		frames++;

		if(currentTime - timer > 1)
		{
			std::cout << "ups: " << updates << "  fps: " << frames << std::endl;
			frames = 0;
			updates = 0;
			timer++;
		}

	}

}

void GameEngine::Update(double delta)
{
	glfwPollEvents();
	sceneManager->Update(delta);
}

void GameEngine::Render(GLFWwindow *window) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sceneManager->Render();

	glfwSwapBuffers(window);
}



GameEngine::~GameEngine(void)
{
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
	if(key && action == GLFW_PRESS)
        Input::setKeyTrue(key);
    if(key && action == GLFW_RELEASE)
        Input::setKeyFalse(key);
}