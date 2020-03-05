#include "pch.h"
#include "Renderer/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Reme {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
	}

	void OrthographicCamera::ReCalc()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
	}
}
