#include <shader.h>

// OpenGL headers
#include <glad/glad.h>

// Standard library headers
#include <string>
#include <fstream>
#include <iostream>

// Get shader file contents as a string
std::string Shader::readShaderFile(std::string shaderPath)
{
    std::string fileString;
    std::string lineString;
    std::ifstream readFile(shaderPath);
    
    // If the file can be opened,
    if (readFile.is_open())
    {
	while (getline(readFile, lineString))
	{
	    fileString.append(lineString);
	    fileString.append("\n");
	}
	readFile.close();
    }
    else
    {
	std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_OPENED\n" << std::endl;
    }
    return fileString;
}

// Class constructor
Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    // Retrieve vertex and fragment shader source code
    std::string vertexSourceString = readShaderFile(vertexShaderPath);
    std::string fragmentSourceString = readShaderFile(fragmentShaderPath);

    // Convert strings to char pointers that OpenGL can use
    const char* vertexShaderSource = vertexSourceString.c_str();
    const char* fragmentShaderSource = fragmentSourceString.c_str(); 

    // Build and compile shader program
    // Compile vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Check if vertex shader has compiled
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Check if the fragment shader has compiled
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Create shader program and link vertex and fragment shaders
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    // Check if the shader program has compiled
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
	glGetProgramInfoLog(ID, 512, NULL, infoLog);
    }
    // De-allocate the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Bind the shader
void Shader::use()
{
    glUseProgram(ID);
}

// Set unforms
void Shader::setBool(const std::string &name, bool value) const
{
    // Get uniform location based on name, and cast bool to 0 or 1
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
