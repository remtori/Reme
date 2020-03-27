#include "pch.h"
#include "Reme/Renderer/Renderer2D.h"
#include "Reme/Renderer/RendererAPI.h"

#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

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
		Ref<Shader> flatShader;
		Ref<VertexArray> VAO;
		Ref<VertexBuffer> VBO;

		// Data for Batch Rendering
		Vertex* buffer;
		uint32_t vertexCount;
		Ref<Texture> currentTexture;
	};

	static const uint32_t MAX_QUAD_COUNT = 10000;
	static const uint32_t MAX_VERTEX_BUFFER_SIZE = MAX_QUAD_COUNT * 4 * sizeof(Vertex);
	static const uint32_t MAX_INDEX_BUFFER_SIZE = MAX_QUAD_COUNT * 6 * sizeof(uint32_t);

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.buffer = new Vertex[MAX_QUAD_COUNT * 4];

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

		auto IBO = IndexBuffer::Create(MAX_INDEX_BUFFER_SIZE);
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
		delete s_Data.buffer;
	}

	void Renderer2D::Begin(const Ref<Camera>& cam)
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
		const Ref<Texture>& tex,
		const glm::vec2& sP, const glm::vec2& sS, float sR,
		const glm::vec2& dP, const glm::vec2& dS, float dR,
		const Color& color
	)
	{
		Ref<Texture> texture = tex == nullptr ? Texture::Default : tex;

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

		if (sR != 0.0f)
		{
			const glm::vec2 centre = { sP.x + sS.x / 2.0f, sP.y + sS.y / 2.0f };
			glm::mat3 rotMat = glm::mat3(1.0f);
			rotMat = glm::translate(rotMat, centre);
			rotMat = glm::rotate(rotMat, sR);
			rotMat = glm::translate(rotMat, -centre);

			for (int i = 1; i <= 4; i++)
			{
				Vertex& v = s_Data.buffer[s_Data.vertexCount - i];
				glm::vec3 p = { v.UV.x, v.UV.y, 0.0f };
				p = p * rotMat;
				v.UV.x = p.x;
				v.UV.y = p.y;
			}
		}

		if (dR != 0.0f)
		{
			const glm::vec2 centre = { dP.x + dS.x / 2.0f, dP.y + dS.y / 2.0f };
			glm::mat3 rotMat = glm::mat3(1.0f);
			rotMat = glm::translate(rotMat, centre);
			rotMat = glm::rotate(rotMat, dR);
			rotMat = glm::translate(rotMat, -centre);

			for (int i = 1; i <= 4; i++)
			{
				Vertex& v = s_Data.buffer[s_Data.vertexCount - i];
				glm::vec3 p = { v.Position.x, v.Position.y, 1.0f };
				p = rotMat * p;
				v.Position.x = p.x;
				v.Position.y = p.y;
			}
		}
	}

	void Renderer2D::DrawRect(const Color& color, const glm::vec2& position, const glm::vec2& scale, float rot)
	{
		Renderer2D::Draw(
			Texture::White,
			{ 0.0f, 0.0f }, { 0.0f, 0.0f }, 0.0f,
			position, scale, rot,
			color
		);
	}

	void Renderer2D::DrawTexture(const Ref<Texture>& texture, const glm::vec2& destPos, const glm::vec2& destScale)
	{
		glm::vec2 dS = destScale;
		if (destScale.x == 0.0f && destScale.y == 0.0f)
		{
			dS = texture == nullptr
				? glm::vec2{ 64.0f, 64.0f }
				: glm::vec2{ texture->GetWidth(), texture->GetHeight() };
		}

		Renderer2D::Draw(
			texture, 
			{ 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f, 
			destPos, dS, 0.0f
		);
	}

	void Renderer2D::DrawTexture(const Ref<Texture>& texture, const glm::vec2& srcPos, const glm::vec2& srcScale, const glm::vec2& destPos, const glm::vec2& destScale)
	{
		glm::vec2 sP, sS;
		sP.x = srcPos.x / texture->GetWidth();
		sP.y = srcPos.y / texture->GetHeight();
		sS.x = srcScale.x / texture->GetWidth();
		sS.y = srcScale.y / texture->GetHeight();

		Renderer2D::Draw(
			texture, 
			sP, sS, 0.0f,
			destPos, destScale, 0.0f
		);
	}
}
