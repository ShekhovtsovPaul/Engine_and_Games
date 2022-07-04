#pragma once

#include "GLTexture.h"

#include <string>


namespace Engine {

	class ImageLoader {
	public:

		// static func - use without instance!
		static GLTexture loadPNG(std::string filePath);	// just load
	};
}
