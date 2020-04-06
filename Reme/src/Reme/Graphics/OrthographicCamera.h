#pragma once

#include "Reme/Graphics/Camera.h"

namespace Reme
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);
		void SetPosition(const glm::vec3& pos) { m_Position = pos; ReCalc(); };
		void SetRotation(float rot) { m_Rotation = rot; ReCalc(); };

		float GetRotation() const { return m_Rotation; };
		const glm::vec3& GetPosition() const { return m_Position; };
		const glm::mat4& GetViewMatrix() const override { return m_ViewMatrix; };
		const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; };
	private:
		void ReCalc();
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}
