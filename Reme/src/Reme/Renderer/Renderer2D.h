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

		static void Begin(const Ref<Camera>& cam);
		static void End();
		static void Flush();
		static void Draw(
			const Ref<Texture>& texture,
			const glm::vec2& srcPos, const glm::vec2& srcScale, float srcRototationRadian,
			const glm::vec2& destPos, const glm::vec2& destScale, float destRotationRadian,
			const Color& color = Color::White
		);
		static void DrawRect(const Color& color, const glm::vec2& position, const glm::vec2& scale);
		static void DrawTexture(const Ref<Texture>& texture, const glm::vec2& destPos, const glm::vec2& destScale = { 0.0f, 0.0f });
		static void DrawTexture(const Ref<Texture>& texture, const glm::vec2& srcPos, const glm::vec2& srcScale, const glm::vec2& destPos, const glm::vec2& destScale);
	};
}
