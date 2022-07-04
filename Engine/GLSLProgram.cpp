#include "GLSLProgram.h"
#include "Errors.h"

#include <vector>
#include <fstream>


namespace Engine {

    // an initialization list. It is a better way to initialize variables, since it avoids an extra copy. 
    GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
    {
    }
    GLSLProgram::~GLSLProgram()
    {
    }

    //Compiles the shaders into a form that your GPU can understand
    void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {

        // init PROGRAM ID
        _programID = glCreateProgram();

        // init Vertex Shader ID
        _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        if (_vertexShaderID == 0)
            fatalError("Vertex shader failed to created!");

        // init Fragment Shader ID
        _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        if (_fragmentShaderID == 0)
            fatalError("Fragment shader failed to created!");

        compileShader(vertexShaderFilePath, _vertexShaderID);
        compileShader(fragmentShaderFilePath, _fragmentShaderID);
    }

    // LINK to ONE PROGRAM !
    void GLSLProgram::linkShaders() {

        //Attach our shaders to our program
        glAttachShader(_programID, _vertexShaderID);
        glAttachShader(_programID, _fragmentShaderID);

        //Link our program
        glLinkProgram(_programID);

        //Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

            //The maxLength includes the NULL character
            std::vector<char> errorLog(maxLength);
            glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

            //We don't need the program anymore.
            glDeleteProgram(_programID);
            //Don't leak shaders either.
            glDeleteShader(_vertexShaderID);
            glDeleteShader(_fragmentShaderID);

            //print the error log and quit
            std::printf("%s\n", &(errorLog[0]));
            fatalError("Shaders failed to link!");
        }

        //Always detach shaders after a successful link.
        glDetachShader(_programID, _vertexShaderID);
        glDetachShader(_programID, _fragmentShaderID);
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);
    }

    // Adds an attribute to our shader. Should be called between compiling and linking.
    void GLSLProgram::addAttribute(const std::string& attributeName)
    {
        glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
    }

    // UNIFORM - return ID (get to SHADER PROGRAM from CPU)
    GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
    {
        GLint location = glGetUniformLocation(_programID, uniformName.c_str());
        if (location == GL_INVALID_INDEX) {
            fatalError("Uniform " + uniformName + " not found in shader!");
        }
        return location;
    }

    // Compiles a single shader file
    void GLSLProgram::compileShader(const std::string& filePath, GLuint id)
    {
        // STREAM to read from SHADERS 
        std::ifstream vertexFile(filePath);
        if (vertexFile.fail()) {
            perror(filePath.c_str());
            fatalError("Failed to open " + filePath);
        }

        std::string fileContents = "";
        std::string line;

        // read in CORRECT ORDER !
        while (std::getline(vertexFile, line))
            fileContents += line + "\n";

        vertexFile.close();

        // HACK TRICK - read array of 'C' strings
        const char* contentsPtr = fileContents.c_str();
        glShaderSource(id, 1, &contentsPtr, nullptr);

        glCompileShader(id);

        // CHECK ERRORs in SHADER SOURCE !
        GLint success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE) {
            // CREATE ERROR_LOG !
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

            glDeleteShader(id);    // don't leak the shader

            std::printf("%s\n", &(errorLog[0]));
            fatalError("Shader " + filePath + " failed to compile");
        }
    }

    //enable the shader, and all its attributes
    void GLSLProgram::use() {
        glUseProgram(_programID);
        //enable all the attributes we added with addAttribute
        for (int i = 0; i < _numAttributes; i++) {
            glEnableVertexAttribArray(i);
        }
    }

    //disable the shader
    void GLSLProgram::unuse() {
        glUseProgram(0);
        for (int i = 0; i < _numAttributes; i++) {
            glDisableVertexAttribArray(i);
        }
    }
}
