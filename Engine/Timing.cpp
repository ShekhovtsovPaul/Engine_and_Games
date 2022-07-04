#include "Timing.h"
#include <SDL/SDL.h>


namespace Engine {

	FpsLimiter::FpsLimiter()
	{
	}
	FpsLimiter::~FpsLimiter()
	{
	}

	void FpsLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}
	void FpsLimiter::setMaxFPS(float maxFPS)
	{
		_maxFPS = maxFPS;
	}
	void FpsLimiter::begin()
	{
		_startTicks = SDL_GetTicks();
	}
	float FpsLimiter::end()
	{
		calculateFPS();

		float frameTicks = SDL_GetTicks() - _startTicks;
		//Limit the FPS to the max FPS
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));
		}

		return _fps;
	}
	// FrameTime - is miliseconds of ONE FRAME (deltaTime dt)
	// FIND - AVERAGE of ALL FrameTimes !
	void FpsLimiter::calculateFPS()
	{
		static const int NUM_SAMPLES = 10;	// number of FRAMES to avarage
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static float prevTicks = SDL_GetTicks();

		float currentTicks;
		currentTicks = SDL_GetTicks();

		_frameTime = currentTicks - prevTicks;	// ONE FRAME in seconds
		frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;	//WRITE to ARRAY

		prevTicks = currentTicks;

		int count;

		currentFrame++;
		if (currentFrame < NUM_SAMPLES)
			count = currentFrame;
		else
			count = NUM_SAMPLES;

		// calculate average
		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++) {
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		if (frameTimeAverage > 0)
			_fps = 1000.0f / frameTimeAverage;
		else
			_fps = 60.0f;
	}

}