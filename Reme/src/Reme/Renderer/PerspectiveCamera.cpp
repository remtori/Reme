#include "reme_pch.h"
#include "Reme/Renderer/PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Reme
{
    PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
        : m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_AspectRatio(1.0), m_FOV(45.0f),
        m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch)
    {
        ReCalc();
    }

    PerspectiveCamera::~PerspectiveCamera()
    {
    }

    void PerspectiveCamera::ReCalc()
    {
        PROFILE_FUNCTION();
        
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);

        // Also re-calculate the Right and Up vector
        // Normalize the vectors, because their length gets closer to 0
        // the more you look up or down which results in slower movement.
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));

        m_viewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        m_projectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, 0.1f, 100.0f);
    }
}
