#include "TextureCache.h";
#include "ImageLoader.h"
#include <iostream>


namespace Engine {

    TextureCache::TextureCache()
    {
    }
    TextureCache::~TextureCache()
    {
    }

    // GET form TEXTURE CACHE ! or ADD TEXTURE to MAP !
    GLTexture TextureCache::getTexture(std::string texturePath) {

        //lookup the texture and see if its in the map
        // std::map<std::string, GLTexture>::iterator mit = 
        auto mit = _textureMap.find(texturePath);

        //check if its not in the map
        if (mit == _textureMap.end()) {
            //Load the texture (rewrite everytime)
            GLTexture newTexture = ImageLoader::loadPNG(texturePath);

            //Insert it into the map
            _textureMap.insert(make_pair(texturePath, newTexture));

            return newTexture;
        }
        return mit->second;
    }
}
