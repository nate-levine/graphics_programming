#include "dependencies/glfw3.h"
#include <iostream>

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
    // Error handling
    if (window == NULL)
    {
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);

    // While window is open
    while (!glfwWindowShouldClose(window))
    {
	// Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);
	// Swap the buffers
        glfwSwapBuffers(window);
	// Poll for events
        glfwPollEvents();
    }

    // Terminate the window
    glfwTerminate();
    // End the program
    return 0;
}


