#pragma once

#include "TextureCache.h"
#include <string>


namespace Engine {

	// STATIC CLASS - NOT need INSTANCE in MainGame!
	// CACHING !!! ALL RESOURCES: texture, model, mesh
	class ResourceManager {
	public:

		// static func - work without instance!
		static GLTexture getTexture(std::string texturePath);
	private:

		// static - map<str, texture> - NOT CHANGE!!!
		static TextureCache _textureCache;	// STORE all TEXTURES!
	};
}
