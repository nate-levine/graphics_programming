// Prevent redefinitions
#ifndef CAMERA_H
#define CAMERA_H

// OpenGL headers
#include <glad/glad.h>

// Resources
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Enum to define movement directions
enum DIRECTION
{
    FORWARD,
    BACKWARD,
    RIGHT,
    LEFT,
};

class Camera
{
private:
    // Orientation
    glm::vec3 m_pos;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    
    // Update camera vectors
    void updateVectors();
public:
    // Class constructor
    Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up);
    // Input
    void processMovement(DIRECTION direction, float deltaTime);
    // Return view/"look at" matrix
    glm::mat4 getViewMatrix();
};

#endif
