#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

// Standard library
#include <iostream>

// Custom includes
#include <shader.h>

// Resources
#include <stb_image.h> // Image loading library
#include <glm/glm.hpp> // Mathematics library
#include <glm/gtc/matrix_transform.hpp>

// Window width and height
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

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
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "graphics_programming", NULL, NULL);
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
	/*position*/		    /*color*/           /*uv*/
    -0.5f,  0.5f,  0.0f,	1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.0f,	0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.0f,	0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.0f,	1.0f, 0.0f, 1.0f,   1.0f, 1.0f,
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 *	sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // uvs
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // Unbind vertex array
    glBindVertexArray(0);
    
    // Textures
    // Create and bind texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Set texture wrapping mode per-axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // Set texture filtering properties
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Load texture image using stb
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../src/images/container.jpg", &width, &height, &nrChannels, 0);
    // Check if the image data is loaded
    if (data)
    {
        // Generate texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // Generate texture mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD" << std::endl;
    }
    // De-allocate image data
    stbi_image_free(data);
    
    // Transform matrices
    shader.use();
    // Model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
    shader.setMatrix4fv("model", model);
    // View
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
    shader.setMatrix4fv("view", view);
    // Projection
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    shader.setMatrix4fv("projection", projection);

    // While window is open
    while (!glfwWindowShouldClose(window))
    {
	    // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Set the active texutre (sampler2D in fragment shader)
        glActiveTexture(GL_TEXTURE0);
        // Bind texture
        glBindTexture(GL_TEXTURE_2D, texture);
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
    glDeleteBuffers(1, &EBO);
	
    // Terminate the window
    glfwTerminate();
    // End the program
    return 0;
}
