#pragma once

#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

namespace Reme
{
	struct Renderable
	{
		Shader* shader;
		Texture* texture;
		glm::vec3* vertexData;
		uint32_t vertexCount;
	};
}
