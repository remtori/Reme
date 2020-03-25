#pragma once

#include "Reme/Renderer/Camera.h"

namespace Reme
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);
		void SetPosition(const glm::vec3& pos) { m_Position = pos; ReCalc(); };
		void SetRotation(const float& rot) { m_Rotation = rot; ReCalc(); };

		glm::vec3 GetPosition() const { return m_Position; };
		float     GetRotation() const { return m_Rotation; };
		glm::mat4 GetViewMatrix() const override { return m_ViewMatrix; };
		glm::mat4 GetProjectionMatrix() const override { return m_ProjectionMatrix; };
	private:
		void ReCalc();
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}
