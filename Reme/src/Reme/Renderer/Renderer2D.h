#pragma once

#include "Reme/Core/Core.h"
#include "Reme/Renderer/Color.h"
#include "Reme/Renderer/Texture.h"
#include "Reme/Renderer/Camera.h"
#include "Reme/Renderer/Shader.h"
#include "Reme/Renderer/Buffers.h"
#include "Reme/Renderer/VertexArray.h"

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

		static void FillRect(const Color& color, float x, float y, float w, float h)
		{
			DrawPartialTexture(Texture::White, 0.0f, 0.0f, 0.0f, 0.0f, x, y, w, h, color);
		}

		static void DrawTexture(const Ref<Texture>& texture, float dX, float dY)
		{
			DrawPartialTexture(
				texture,
				0.0f, 0.0f, texture->GetWidth(), texture->GetHeight(),
				dX, dY, texture->GetWidth(), texture->GetHeight()
			);
		}

		static void DrawTexture(const Ref<Texture>& texture, float dX, float dY, float dW, float dH)
		{
			DrawPartialTexture(
				texture,
				0.0f, 0.0f, texture->GetWidth(), texture->GetHeight(),
				dX, dY, dW, dH
			);
		}

		static void DrawPartialTexture(
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
			
		struct Vertex
		{
			glm::vec2 Position;
			glm::vec2 UV;
			glm::vec4 Color;
			float TexIndex;
		};

		struct Data
		{
			Ref<Shader> flatShader;
			Ref<VertexArray> VAO;
			Ref<VertexBuffer> VBO;

			// Data for Batch Rendering
			Vertex* buffer;
			uint32_t vertexIndex;

			std::vector<WeakRef<Texture>> textures;
			uint32_t textureIndex;
		};
	private:
		static void Flush();
	};
}
