// Prevent redefinitions
#ifndef SHADER_H
#define SHADER_H

// OpenGL headers
#include <glad/glad.h>

// Standard library headers
#include <string>

// Resources
#include <glm/glm.hpp> // Math library
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
    // Shader program ID
    unsigned int ID;

    // Get shader file contents as a string
    std::string readShaderFile(std::string shaderPath);
public:
    // Class constructor
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
    // Bind the shader
    void use();
    // Set uniforms
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMatrix4fv(const std::string &name, glm::mat4 value) const;
};

#endif
