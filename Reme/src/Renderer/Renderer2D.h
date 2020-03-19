#pragma once

#include <unordered_map>

#include "Renderer/Color.h"
#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include "Renderer/Buffers.h"
#include "Renderer/VertexArray.h"

#define MAX_VERTEX_SIZE 65535
#define FLOAT_PER_VERTEX 8
#define VERTEX_PER_DRAWABLE 6

namespace Reme
{
	struct Vertex 
	{
		union 
		{
			struct { float x, y, U, V, color[4]; };
			float __data[FLOAT_PER_VERTEX];
		};
	};

	struct Drawable
	{		
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
		VertexBuffer* vertexBuffer;
		std::vector<Drawable> elements;
		float* buffer;
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
