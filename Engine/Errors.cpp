#include "Errors.h"

#include <cstdlib>
#include <SDL/SDL.h>
#include <iostream>


namespace Engine {

	void fatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit... ";
		int tmp;
		std::cin >> tmp;
		SDL_Quit();		// close all GAME
		exit(69);
	}
}
