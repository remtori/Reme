#pragma once

#include <unordered_map>

#include "Renderer/Color.h"
#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include "Renderer/Buffers.h"
#include "Renderer/VertexArray.h"

namespace Reme
{
	const uint32_t MAX_VERTEX_BUFFER_SIZE = 4000000;
	const uint32_t FLOAT_PER_VERTEX = 8;
	const uint32_t VERTEX_PER_DRAWABLE = 6;
	const uint32_t MAX_DRAWABLE_PER_BATCH = (MAX_VERTEX_BUFFER_SIZE / (VERTEX_PER_DRAWABLE * FLOAT_PER_VERTEX * sizeof(float)));

	struct Vertex 
	{
		float x, y, U, V;
	};

	struct Drawable
	{		
		Color color;
		Texture* texture;
		Vertex vertexArray[VERTEX_PER_DRAWABLE];
	};

	struct Renderer2DData
	{
		Shader* flatShader;
		Texture* whiteTexture;
		Texture* rgbTexture;
		// OpenGL Stuff
		VertexArray* VAO;
		VertexBuffer* VBO;
		std::vector<Drawable> drawables;
	};

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
			glm::vec2 srcPos, glm::vec2 srcScale,
			glm::vec2 destPos, glm::vec2 destScale,
			Color color = Color::White
		);
	public:
		static Renderer2DData* m_Data;
	};
}
