#pragma once

#include "Renderer/Camera.h"

namespace Reme
{
	class OrthographicCamera : Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; ReCalc(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; ReCalc(); }

		glm::mat4 GetViewMatrix() const override;
		glm::mat4 GetProjectionMatrix() const override;
	private:
		void ReCalc();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}
