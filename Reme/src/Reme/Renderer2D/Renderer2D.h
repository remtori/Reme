#pragma once

#include "Reme/Core/Core.h"
#include "Reme/Renderer/Color.h"
#include "Reme/Renderer/Texture.h"
#include "Reme/Renderer/Camera.h"

#include <glm/glm.hpp>

namespace Reme
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void Begin(const Ref<Camera>& cam);
		static void End();

		// Basic Quad Drawing API
		static void Draw(
			const Ref<Texture>& texture,
			const glm::vec2& srcPos, const glm::vec2& srcSize,
			const glm::vec2& destPos, const glm::vec2& destSize,
			const Color& color = Color::White
		);
		static void DrawRect(const Color& color, const glm::vec2& position, const glm::vec2& size);
		static void DrawTexture(const Ref<Texture>& texture, const glm::vec2& destPos, const glm::vec2& destSize = { 0.0f, 0.0f });
		static void DrawTexture(const Ref<Texture>& texture, const glm::vec2& srcPos, const glm::vec2& srcSize, const glm::vec2& destPos, const glm::vec2& destScale);

		// Transformation
		static void PushState();
		static void PopState();

		static const glm::mat3& GetTransform();
		static void SetTransform(const glm::mat3& mat);

		static void Translate(const glm::vec2& vec);
		static void Scale(const glm::vec2& vec);
		static void Rotate(float rotRadian);
	private:
		static void Flush();
	};
}
