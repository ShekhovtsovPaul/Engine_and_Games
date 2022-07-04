#pragma once

#include <GL/glew.h>

#include "GLTexture.h"
#include <string>


namespace Engine {

	class Sprite {
	public:

		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, std::string texturePath);	// LOAD MODEL
		void draw();
	private:

		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vboID;		// array of vertices - store in GPU
		GLTexture _texture;
	};
}
