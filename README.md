# graphics_programming
For graphics programming endeavors

----------------

GLFW SETUP:
# download and extract GLFW 64-bit Windows binaries
https://www.glfw.org/download.html
# in the project root directory
$ mkdir dependencies
# in ./dependencies, paste in files from GLFW
- libglfw3.a
- glfw3.h

----------------

COMPILATION:
# navigate to the project root directory:
# compile the program
g++ main.cpp -I dependencies .\dependencies\libglfw3.a -lopengl32 -lgdi32 -o main.exe
# execute the program
./main.exe

----------------

TEST:
# This code should make a window appear

#include "dependencies/glfw3.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
