#include "pch.h"
#include "Reme/Renderer/Renderer2D.h"
#include "Reme/Renderer/RendererAPI.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Reme
{
	struct Vertex
	{
		glm::vec2 Position;
		glm::vec2 UV;
		glm::vec4 Color;
	};

	struct Renderer2DData
	{
		Shader* flatShader;
		Texture* whiteTexture;
		Texture* rgbTexture;
		VertexArray* VAO;
		VertexBuffer* VBO;

		// Data for Batch Rendering
		Vertex* buffer;
		uint32_t vertexCount;
		Texture* currentTexture;
	};

	static const uint32_t MAX_QUAD_COUNT = 10000;
	static const uint32_t MAX_VERTEX_BUFFER_SIZE = MAX_QUAD_COUNT * 4 * sizeof(Vertex);
	static const uint32_t MAX_INDEX_BUFFER_SIZE = MAX_QUAD_COUNT * 6 * sizeof(uint32_t);

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.buffer = new Vertex[MAX_QUAD_COUNT * 4];

		s_Data.whiteTexture = Texture::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data.rgbTexture = Texture::Create(2, 2);
		uint32_t rgbTextureData[] = { 0xff0000ff, 0xff00ff00, 0xffff0000, 0xffffffff };
		s_Data.rgbTexture->SetData(&rgbTextureData, sizeof(rgbTextureData));

		s_Data.flatShader = Shader::Create("Flat Shader",
			// Vertex shader
			"#version 330 core\n"

			"uniform mat4 viewMat;\n"
			"uniform mat4 projMat;\n"

			"layout (location = 0) in vec2 Position;\n"
			"layout (location = 1) in vec2 UV;\n"
			"layout (location = 2) in vec4 Color;\n"

			"out vec2 Frag_UV;\n"
			"out vec4 Frag_Color;\n"

			"void main()\n"
			"{\n"
			"	  gl_Position = projMat * viewMat * vec4(Position, 0, 1);\n"
			"	  Frag_UV = UV;\n"
			"     Frag_Color = Color;\n"
			"}\n",
			// Fragment shader
			"#version 330 core\n"

			"uniform sampler2D Texture;\n"

			"in vec2 Frag_UV;\n"
			"in vec4 Frag_Color;\n"

			"out vec4 Out_Color;\n"

			"void main()\n"
			"{\n"
			"    Out_Color = Frag_Color * texture(Texture, Frag_UV);\n"
			"}\n"
		);

		s_Data.flatShader->Bind();
		s_Data.flatShader->SetInt("Texture", 0);

		s_Data.VAO = VertexArray::Create();

		s_Data.VBO = VertexBuffer::Create(MAX_VERTEX_BUFFER_SIZE, false);
		s_Data.VBO->SetLayout({
			{ ShaderDataType::Float2, "Position" },
			{ ShaderDataType::Float2, "UV" },
			{ ShaderDataType::Float4, "Color" },
		});
		s_Data.VAO->AddVertexBuffer(s_Data.VBO);

		IndexBuffer* IBO = IndexBuffer::Create(MAX_INDEX_BUFFER_SIZE);
		uint32_t* indexes = new uint32_t[MAX_INDEX_BUFFER_SIZE / sizeof(uint32_t)];
		uint32_t offset = 0;

		for (int i = 0; i < MAX_INDEX_BUFFER_SIZE / sizeof(uint32_t); i += 6)
		{
			indexes[i + 0] = offset + 0;
			indexes[i + 1] = offset + 1;
			indexes[i + 2] = offset + 2;
			indexes[i + 3] = offset + 1;
			indexes[i + 4] = offset + 2;
			indexes[i + 5] = offset + 3;
			offset += 4;
		}

		IBO->SetData(indexes, 0, MAX_INDEX_BUFFER_SIZE);
		s_Data.VAO->SetIndexBuffer(IBO);
		delete[] indexes;

		RenderCommand::SetClearColor(Color(0x696969ff));
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data.flatShader;
		delete s_Data.whiteTexture;
		delete s_Data.rgbTexture;
		delete s_Data.VBO;
		delete s_Data.VAO;
	}

	void Renderer2D::Begin(Camera* cam)
	{
		RenderCommand::Clear();
		s_Data.flatShader->Bind();
		s_Data.flatShader->SetMat4("viewMat", cam->GetViewMatrix());
		s_Data.flatShader->SetMat4("projMat", cam->GetProjectionMatrix());

		s_Data.VAO->Bind();

		s_Data.vertexCount = 0;
		s_Data.currentTexture = nullptr;
	}

	void Renderer2D::End()
	{
		Flush();
		s_Data.VAO->Unbind();
		RenderCommand::PollError();
	}

	void Renderer2D::Flush()
	{
		if (s_Data.vertexCount == 0) return;

		s_Data.currentTexture->Bind();
		s_Data.VBO->SetData((float*) s_Data.buffer, 0, s_Data.vertexCount * sizeof(Vertex));
		RenderCommand::DrawIndexed(s_Data.vertexCount / 4 * 6);

		s_Data.vertexCount = 0;
		s_Data.currentTexture = nullptr;
	}

	void Renderer2D::Draw(
		Texture* texture,
		glm::vec2 sP, glm::vec2 sS,
		glm::vec2 dP, glm::vec2 dS,
		Color color
	)
	{
		if (texture == 0) texture = s_Data.rgbTexture;
		else if (texture == (void*) 1) texture = s_Data.whiteTexture;

		if (
			(s_Data.currentTexture != nullptr && texture != s_Data.currentTexture) ||
			s_Data.vertexCount > MAX_QUAD_COUNT
		)
		{
			Flush();
		}

		s_Data.currentTexture = texture;
		glm::vec4 c = { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };

		s_Data.buffer[s_Data.vertexCount].Position = { dP.x       , dP.y        };
		s_Data.buffer[s_Data.vertexCount].UV       = { sP.x       , sP.y        };
		s_Data.buffer[s_Data.vertexCount].Color    = c;
		s_Data.vertexCount++;

		s_Data.buffer[s_Data.vertexCount].Position = { dP.x + dS.x, dP.y        };
		s_Data.buffer[s_Data.vertexCount].UV       = { sP.x + sS.x, sP.y        };
		s_Data.buffer[s_Data.vertexCount].Color    = c;
		s_Data.vertexCount++;

		s_Data.buffer[s_Data.vertexCount].Position = { dP.x       , dP.y + dS.y };
		s_Data.buffer[s_Data.vertexCount].UV       = { sP.x       , sP.y + sS.y };
		s_Data.buffer[s_Data.vertexCount].Color    = c;
		s_Data.vertexCount++;

		s_Data.buffer[s_Data.vertexCount].Position = { dP.x + dS.x, dP.y + dS.y };
		s_Data.buffer[s_Data.vertexCount].UV       = { sP.x + sS.x, sP.y + sS.y };
		s_Data.buffer[s_Data.vertexCount].Color    = c;
		s_Data.vertexCount++;
	}

	void Renderer2D::DrawRect(Color color, glm::vec2 position, glm::vec2 scale)
	{
		// Renderer2D Draw implementation will convert
		// (Texture*) 1 to a white texture
		Renderer2D::Draw(
			(Texture*) 1,
			{ 0.0f, 0.0f }, { 0.0f, 0.0f },
			position, scale,
			color
		);
	}

	void Renderer2D::DrawTexture(Texture* texture, glm::vec2 destPos, glm::vec2 destScale)
	{
		if (destScale.x == 0.0f && destScale.y == 0.0f)
		{
			destScale = texture == nullptr
				? glm::vec2{ 64.0f, 64.0f }
				: glm::vec2{ texture->GetWidth(), texture->GetHeight() };
		}

		Renderer2D::Draw(texture, { 0.0f, 0.0f }, { 1.0f, 1.0f }, destPos, destScale);
	}

	void Renderer2D::DrawTexture(Texture* texture, glm::vec2 srcPos, glm::vec2 srcScale, glm::vec2 destPos, glm::vec2 destScale)
	{
		srcPos.x /= texture->GetWidth();
		srcPos.y /= texture->GetHeight();
		srcScale.x /= texture->GetWidth();
		srcScale.y /= texture->GetHeight();

		Renderer2D::Draw(texture, srcPos, srcScale, destPos, destScale);
	}
}
