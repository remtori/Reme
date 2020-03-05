#pragma once

#include "Renderer/Camera.h"

namespace Reme
{
	class PerspectiveCamera : Camera
	{
	public:
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;

		// Euler Angles
		float Yaw;
		float Pitch;

		// Field of view
		float FOV;
		float aspectRatio;

		PerspectiveCamera(
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = -90.0f,
			float pitch = 0.0f
		);
		~PerspectiveCamera();

		glm::mat4 GetViewMatrix() const override;
		glm::mat4 GetProjectionMatrix() const override;
		void ReCalc();
	};
}
