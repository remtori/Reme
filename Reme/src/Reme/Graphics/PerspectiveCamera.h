#pragma once

#include "Reme/Graphics/Camera.h"

namespace Reme
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(
			const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
			const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = -90.0f,
			float pitch = 0.0f
		);
		~PerspectiveCamera();

		void SetPosition(const glm::vec3& pos)  { m_Position    = pos;   ReCalc(); };
		void SetWorldUp(const glm::vec3& up)    { m_WorldUp     = up;    ReCalc(); };
		void SetYaw(float yaw)           { m_Yaw         = yaw;   ReCalc(); };
		void SetPitch(float pitch)       { m_Pitch       = pitch; ReCalc(); };
		void SetFOV(float fov)           { m_FOV         = fov;   ReCalc(); };
		void SetAspectRatio(float ratio) { m_AspectRatio = ratio; ReCalc(); };

		const glm::vec3& GetPosition()    { return m_Position;    };
		const glm::vec3& GetWorldUp()     { return m_WorldUp;     };
		float GetYaw()         { return m_Yaw;         };
		float GetPitch()       { return m_Pitch;       };
		float GetFOV()         { return m_FOV;         };
		float GetAspectRatio() { return m_AspectRatio; };

		const glm::mat4& GetViewMatrix() const override { return m_viewMatrix; };
		const glm::mat4& GetProjectionMatrix() const override { return m_projectionMatrix; };

	private:
		void ReCalc();
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;

		// Internal value for calculation
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;

		glm::vec3 m_Position;
		glm::vec3 m_WorldUp;

		// Euler Angles
		float m_Yaw;
		float m_Pitch;

		// Field of view
		float m_FOV;
		float m_AspectRatio;
	};
}
