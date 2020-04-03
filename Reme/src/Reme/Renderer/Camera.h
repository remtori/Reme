#pragma once

#include <glm/glm.hpp>

namespace Reme
{
	class Camera
	{
	public:
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
	};
}
