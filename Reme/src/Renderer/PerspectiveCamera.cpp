#include "pch.h"
#include "Renderer/PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Reme
{
    PerspectiveCamera::PerspectiveCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), aspectRatio(1.0), FOV(45.0f)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        ReCalc();
    }

    PerspectiveCamera::~PerspectiveCamera()
    {
    }

    glm::mat4 PerspectiveCamera::GetProjectionMatrix() const
    {
        return glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, 100.0f);
    }

    glm::mat4 PerspectiveCamera::GetViewMatrix() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void PerspectiveCamera::ReCalc()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
}
