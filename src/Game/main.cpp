#include <iostream>
#include "../Engine/Core/GameEngine.h"
#include "TestSceneManager.h"

int main(void)
{
	{
		std::cout << "Game Engine" << std::endl;

		TestSceneManager manager;

		GameEngine gameEngine(640, 480, 60, &manager);
		gameEngine.Start();
	}

	std::getchar();
}