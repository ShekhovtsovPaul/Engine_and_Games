#include "IOManager.h"

#include <fstream>


namespace Engine {

    bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
        std::ifstream file(filePath, std::ios::binary); // FLAG - READ in BINARY
        if (file.fail()) {
            perror(filePath.c_str());
            return false;
        }

        //seek to the end - TO RESIZE VECTOR, NEED KNOW SIZE?!
        file.seekg(0, std::ios::end);

        //Get the file size
        int fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        //Reduce the file size by any header bytes that might be present
        fileSize -= file.tellg();

        buffer.resize(fileSize);    // NEW FILE SIZE
        file.read((char*)&(buffer[0]), fileSize);  //LOAD TO BUFFER !
        file.close();

        return true;
    }
}
