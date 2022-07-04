#pragma once

#include <map>
#include "GLTexture.h"
#include <string>


namespace Engine {

	// STORE TEXTURE OBJECTS !
	class TextureCache {
	public:

		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texturePath);	// use loadPNG

	private:

		std::map<std::string, GLTexture> _textureMap;	// get from ITERATOR!
	};
}
