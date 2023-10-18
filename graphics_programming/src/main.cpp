#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

// Standard library
#include <iostream>

// Custom includes
#include <shader.h>

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

    // Build and compile shader using custom class
    Shader shader("../src/vertex.shader", "../src/fragment.shader");

    // Vertices data
    float vertices[] =
    {
	/*position*/		/*color*/
        -0.5f,  0.5f,  0.0f,	1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.0f,	0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.0f,	0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.0f,	1.0f, 0.0f, 1.0f,
    };
    // Indices data
    unsigned int indices[] =
    {
	0, 1, 2,
	0, 2, 3,
    };

    // Create vertex array, vertex buffer and element buffers
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind vertex array
    glBindVertexArray(VAO);

    // Bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Pass data to vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Bind element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Pass data to element buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // Format buffer vertex attribute(s)
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 *	sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Unbind vertex array
    glBindVertexArray(0);

    // While window is open
    while (!glfwWindowShouldClose(window))
    {
	// Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);
	// Bind shader program
	shader.use();
	// Bind vertex array
	glBindVertexArray(VAO);
	// Draw vertices
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Swap the buffers
        glfwSwapBuffers(window);
	// Poll for events
        glfwPollEvents();
    }

    // De-allocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
	
    // Terminate the window
    glfwTerminate();
    // End the program
    return 0;
}


