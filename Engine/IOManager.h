#pragma once

#include <string>
#include <vector>


namespace Engine {

	// ONE INSTANCE ! IOManager::readFileToBuffer() - NO OBJECT !
	class IOManager {
	public:

		// READ FILE (TEXTURE) to a BUFFER (VBO)
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}
