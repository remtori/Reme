#pragma once

#include "Reme/Core/Core.h"
#include "Reme/Renderer/Color.h"
#include "Reme/Renderer/Texture.h"
#include "Reme/Renderer/Camera.h"
#include "Reme/Renderer2D/Path2D.h"

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

		static void DrawRect(const Color& color, float x, float y, float w, float h)
		{
			DrawTexture(Texture::White, 0.0f, 0.0f, 0.0f, 0.0f, x, y, w, h, color);
		}

		static void DrawTexture(const Ref<Texture>& texture, float dX, float dY)
		{
			DrawTexture(
				texture,
				0.0f, 0.0f, texture->GetWidth(), texture->GetHeight(),
				dX, dY, texture->GetWidth(), texture->GetHeight()
			);
		}

		static void DrawTexture(const Ref<Texture>& texture, float dX, float dY, float dW, float dH)
		{
			DrawTexture(
				texture,
				0.0f, 0.0f, texture->GetWidth(), texture->GetHeight(),
				dX, dY, dW, dH
			);
		}

		static void DrawTexture(
			const Ref<Texture>& texture,
			float sX, float sY, float sW, float sH,
			float dX, float dY, float dW, float dH,
			const Color& color = Color::White
		);

		// Transformation
		static void PushState();
		static void PopState();

		static const glm::mat3& GetTransform();
		static void SetTransform(const glm::mat3& mat);

		static void Translate(float x, float y);
		static void Scale(float x, float y);
		static void Rotate(float rotRadian);
	private:
		static void Flush();
	};
}
