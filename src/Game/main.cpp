#include <iostream>
#include "../Engine/Core/GameEngine.h"
#include "TestSceneManager.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(void)
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	{
		std::cout << "Game Engine" << std::endl;

		TestSceneManager manager;

		GameEngine gameEngine(640, 480, 60, &manager);
		gameEngine.Start();
	}

	std::getchar();
}