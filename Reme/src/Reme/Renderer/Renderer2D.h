#pragma once

#include <unordered_map>

#include "Reme/Renderer/Color.h"
#include "Reme/Renderer/Camera.h"
#include "Reme/Renderer/Shader.h"
#include "Reme/Renderer/Texture.h"
#include "Reme/Renderer/Buffers.h"
#include "Reme/Renderer/VertexArray.h"

namespace Reme
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void Begin(Camera* cam);
		static void End();
		static void Flush();
		static void Draw(
			Texture* texture,
			glm::vec2 srcPos, glm::vec2 srcScale, float srcRototationRadian,
			glm::vec2 destPos, glm::vec2 destScale, float destRotationRadian,
			Color color = Color::White
		);
		static void DrawRect(Color color, glm::vec2 position, glm::vec2 scale);
		static void DrawTexture(Texture* texture, glm::vec2 destPos, glm::vec2 destScale = { 0.0f, 0.0f });
		static void DrawTexture(Texture* texture, glm::vec2 srcPos, glm::vec2 srcScale, glm::vec2 destPos, glm::vec2 destScale);
	};
}
