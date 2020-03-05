#pragma once

#include <unordered_map>

#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

namespace Reme
{
	struct Renderer2DData
	{
		Shader* flatShader;
		Texture* whiteTexture;
		Texture* rgbTexture;
		// OpenGL Stuff
		uint32_t VAO;
		uint32_t vertexBuffer;
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void Begin(Camera* cam);
		static void End();
		static void Draw(
			Texture* texture,
			glm::vec2 srcPos, glm::vec2 srcScale,
			glm::vec3 destPos, glm::vec2 destScale,
			glm::vec4 tintColor = { 1.0f, 1.0f, 1.0f, 1.0f }
		);

	public:
		static Renderer2DData* m_Data;
	};
}
