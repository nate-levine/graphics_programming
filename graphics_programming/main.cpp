#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main()
{
    // Initialize GLFW
    glfwInit();
    // Configure GLFW Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Configure GLFW to use core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initialize window
    GLFWwindow* window = glfwCreateWindow(800, 600, "graphics_programming", NULL, NULL);
    // Error handling to make sure GLFW is initialized
    if (window == NULL)
    {
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);
    
    // Error handling to make sure GLAD is initialized
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }	

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
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check if the shader program has compiled
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }
    // De-allocate the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Vertices data
    float vertices[] =
    {
	-0.5f, -0.5f,  0.0f,
	 0.5f, -0.5f,  0.0f,
	 0.0f,  0.5f,  0.0f,
    };

    // Create vertex array and vertex buffer
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind vertex array
    glBindVertexArray(VAO);
    // Bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Pass data to buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Format buffer vertex attribute(s)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 *	sizeof(float), (void*)0);
    // Enable vertex attribute
    glEnableVertexAttribArray(0);
    // Unbind vertex array
    glBindVertexArray(0);

    // While window is open
    while (!glfwWindowShouldClose(window))
    {
	// Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);
	// Bind shader program
	glUseProgram(shaderProgram);
	// Bind vertex array
	glBindVertexArray(VAO);
	// Draw vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Swap the buffers
        glfwSwapBuffers(window);
	// Poll for events
        glfwPollEvents();
    }

    // De-allocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Terminate the window
    glfwTerminate();
    // End the program
    return 0;
}


