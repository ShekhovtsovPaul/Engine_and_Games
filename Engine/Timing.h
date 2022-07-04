#pragma once

namespace Engine {

	class FpsLimiter {
	public:

		FpsLimiter();
		~FpsLimiter();

		void init(float maxFPS);
		void setMaxFPS(float maxFPS);
		void begin();
		float end();	// will return FPS
		
	private:

		void calculateFPS();

		float _fps;	//when run ...f
		float _maxFPS;	//limit 60.0f
		float _frameTime;	// ONE frame

		unsigned int _startTicks;
	};



}