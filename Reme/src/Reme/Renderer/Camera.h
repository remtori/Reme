#pragma once

#include <glm/glm.hpp>

namespace Reme
{
	class Camera
	{
	public:
		virtual glm::mat4 GetViewMatrix() const = 0;
		virtual glm::mat4 GetProjectionMatrix() const = 0;
	};
}
