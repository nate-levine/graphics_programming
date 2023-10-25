#include <camera.h>

// Update camera vectors
void Camera::updateVectors()
{
    m_right = glm::normalize(glm::cross(m_front, m_up));
}

// Class constructor
Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
{
    m_pos = pos;
    m_front = front;
    m_up = up;

    updateVectors();
}

// Input
void Camera::processMovement(DIRECTION direction, float deltaTime)
{
    if (direction == FORWARD)  m_pos += m_front * deltaTime;
    if (direction == BACKWARD) m_pos -= m_front * deltaTime;
    if (direction == RIGHT)    m_pos += m_right * deltaTime;
    if (direction == LEFT)     m_pos -= m_right * deltaTime;

    // Update camera axes
    updateVectors();
}

// Return view/"look at" matrix
glm::mat4 Camera::getViewMatrix()
{
    glm::mat4 lookAt = glm::lookAt(m_pos, m_pos + m_front, m_up);
    return lookAt;
}
