#include "Engine.h"
#include <SDL/SDL.h>
#include <GL/glew.h>


namespace Engine {

	int init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);		// one - double buffer!

		return 0;
	}
}
