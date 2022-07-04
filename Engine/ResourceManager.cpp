#include "ResourceManager.h"


namespace Engine {

	// static var - need declare again in .cpp!
	TextureCache ResourceManager::_textureCache;

	GLTexture ResourceManager::getTexture(std::string texturePath) {
		return _textureCache.getTexture(texturePath);
	}
}
