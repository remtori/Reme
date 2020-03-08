#pragma once

#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

namespace Reme
{
	class BatchRenderer
	{
	public:
		BatchRenderer();
		~BatchRenderer();

	private:
		uint32_t m_MAX_VERTEX_COUNT;
		
	};
}
