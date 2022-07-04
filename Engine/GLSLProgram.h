#pragma once

#include <string>
#include <GL/glew.h>		// when use OpenGL


namespace Engine {

    class GLSLProgram {
    public:

        GLSLProgram();
        ~GLSLProgram();

        void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
        void linkShaders();
        void addAttribute(const std::string& attributeName);
        GLint getUniformLocation(const std::string& uniformName);

        void use();
        void unuse();

    private:

        int _numAttributes;

        void compileShader(const std::string& filePath, GLuint id);

        GLuint _programID;		// unique ID
        GLuint _vertexShaderID;		// unique ID
        GLuint _fragmentShaderID;		// unique ID
    };
}
