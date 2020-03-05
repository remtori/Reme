#pragma once

#include "Renderer/Camera.h"

namespace Reme
{
	class OrthographicCamera : public Camera
	{
	public:
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		float Rotation = 0.0f;

		OrthographicCamera(float left, float right, float bottom, float top);

		glm::mat4 GetViewMatrix() const override { return m_ViewMatrix; };
		glm::mat4 GetProjectionMatrix() const override { return m_ProjectionMatrix; };

		void ReCalc() override;
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;		
	};
}
