#include "reme_pch.h"
#include "Reme/Graphics/Renderer2D.h"

#include "Reme/Graphics/RendererAPI.h"

#include "Reme/Graphics/Shader.h"
#include "Reme/Graphics/Buffers.h"
#include "Reme/Graphics/VertexArray.h"

#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

namespace Reme
{
	static const uint32_t MAX_QUAD_COUNT = 100000;

	struct Vertex
	{
		glm::vec2 Position;
		glm::vec2 UV;
		glm::vec4 Color;
		float TexIndex;
	};

	struct Renderer2DData
	{
		Ref<Shader> flatShader;
		Ref<VertexArray> VAO;
		Ref<VertexBuffer> VBO;

		// Data for Batch Rendering
		Vertex* buffer;
		uint32_t vertexIndex;

		std::vector<Ref<Texture>> textures;
		uint32_t textureIndex;
	};

	static const uint32_t MAX_VERTEX_BUFFER_SIZE = MAX_QUAD_COUNT * 4 * sizeof(Vertex);
	static const uint32_t MAX_INDEX_BUFFER_SIZE = MAX_QUAD_COUNT * 6 * sizeof(uint32_t);
	static uint32_t MAX_TEXTURE_UNIT;

	static Renderer2DData s_Data;
	static std::vector<glm::mat3> s_TransformStack;

	void Renderer2D::Init()
	{
		s_TransformStack.push_back(glm::mat3(1.0f));
		s_Data.buffer = new Vertex[MAX_QUAD_COUNT * 4];

		MAX_TEXTURE_UNIT = RenderCommand::GetMaxTextureUnit();
		for (int i = 0; i < MAX_TEXTURE_UNIT; i++)
			s_Data.textures.emplace_back(nullptr);

		s_Data.flatShader = Shader::Create("Flat Shader",
			// Vertex shader
			"#version 330 core\n"

			"uniform mat4 viewMat;\n"
			"uniform mat4 projMat;\n"

			"layout (location = 0) in vec2 Position;\n"
			"layout (location = 1) in vec2 UV;\n"
			"layout (location = 2) in vec4 Color;\n"
			"layout (location = 3) in float TexIndex;\n"

			"out vec2 Frag_UV;\n"
			"out vec4 Frag_Color;\n"
			"out float Frag_TexIndex;\n"

			"void main()\n"
			"{\n"
			"	  Frag_UV = UV;\n"
			"     Frag_Color = Color;\n"
			"     Frag_TexIndex = TexIndex;\n"
			"	  gl_Position = projMat * viewMat * vec4(Position, 0, 1);\n"
			"}\n",
			// Fragment shader
			"#version 330 core\n"

			"in vec2 Frag_UV;\n"
			"in vec4 Frag_Color;\n"
			"in float Frag_TexIndex;\n"

			"out vec4 Out_Color;\n"

			"uniform sampler2D Textures[6];\n"

			"void main()\n"
			"{\n"
			"    vec4 texColor;\n"
			"    if (Frag_TexIndex < 0.5) texColor = texture(Textures[0], Frag_UV);\n"
			"    else if (Frag_TexIndex < 1.5) texColor = texture(Textures[1], Frag_UV);\n"
			"    else if (Frag_TexIndex < 2.5) texColor = texture(Textures[2], Frag_UV);\n"
			"    else if (Frag_TexIndex < 3.5) texColor = texture(Textures[3], Frag_UV);\n"
			"    else if (Frag_TexIndex < 4.5) texColor = texture(Textures[4], Frag_UV);\n"
			"    else texColor = texture(Textures[5], Frag_UV);\n"

			"    Out_Color = Frag_Color * texColor;\n"
			"}\n"
		);

		s_Data.flatShader->Bind();

		int32_t* uTexIndexs = new int32_t[MAX_TEXTURE_UNIT];
		for (int i = 0; i < MAX_TEXTURE_UNIT; i++) uTexIndexs[i] = i;
		s_Data.flatShader->SetIntArray("Textures", uTexIndexs, MAX_TEXTURE_UNIT);
		delete[] uTexIndexs;

		s_Data.VAO = VertexArray::Create();
		s_Data.VBO = VertexBuffer::Create(MAX_VERTEX_BUFFER_SIZE, false);
		s_Data.VBO->SetLayout({
			{ ShaderDataType::Float2, "Position" },
			{ ShaderDataType::Float2, "UV" },
			{ ShaderDataType::Float4, "Color" },
			{ ShaderDataType::Float, "TexIndex" },
		});
		s_Data.VAO->AddVertexBuffer(s_Data.VBO);

		uint32_t offset = 0;
		uint32_t* indicies = new uint32_t[MAX_INDEX_BUFFER_SIZE / sizeof(uint32_t)];
		for (uint32_t i = 0; i < MAX_INDEX_BUFFER_SIZE / sizeof(uint32_t); i += 6)
		{
			indicies[i + 0] = offset + 0;
			indicies[i + 1] = offset + 1;
			indicies[i + 2] = offset + 2;
			indicies[i + 3] = offset + 1;
			indicies[i + 4] = offset + 2;
			indicies[i + 5] = offset + 3;
			offset += 4;
		}
		Ref<IndexBuffer> IBO = IndexBuffer::Create(MAX_INDEX_BUFFER_SIZE);
		IBO->SetData(indicies, 0, MAX_INDEX_BUFFER_SIZE);
		s_Data.VAO->SetIndexBuffer(IBO);
		delete[] indicies;

		s_Data.vertexIndex = 0;
		s_Data.textureIndex = 0;
	}

	void Renderer2D::Shutdown()
	{
		s_Data.flatShader = nullptr;
		s_Data.VBO = nullptr;
		s_Data.VAO = nullptr;
		delete s_Data.buffer;
	}

	void Renderer2D::Begin(const Ref<Camera>& cam)
	{
		RenderCommand::Clear();
		s_Data.flatShader->Bind();
		s_Data.flatShader->SetMat4("viewMat", cam->GetViewMatrix());
		s_Data.flatShader->SetMat4("projMat", cam->GetProjectionMatrix());

		s_Data.VAO->Bind();
	}

	void Renderer2D::End()
	{
		Flush();
		s_Data.VAO->Unbind();
		RenderCommand::PollError();
	}

	void Renderer2D::Flush()
	{
		if (s_Data.vertexIndex == 0) return;

		for (int i = 0; i < s_Data.textureIndex; i++)
			s_Data.textures[i]->Bind(i);

		s_Data.VBO->SetData((float*) s_Data.buffer, 0, s_Data.vertexIndex * sizeof(Vertex));
		RenderCommand::DrawIndexed(DrawMode::TRIANGLES, s_Data.vertexIndex / 4 * 6);

		s_Data.vertexIndex = 0;
		s_Data.textureIndex = 0;
		for (auto& p : s_Data.textures) p.reset();
	}

	void Renderer2D::DrawTexture(
		const Ref<Texture>& tex,
		float sX, float sY, float sW, float sH,
		float dX, float dY, float dW, float dH,
		const Color& color
	)
	{
		Ref<Texture> texture = tex == nullptr ? Texture::Default : tex;

		float TexIndex = -1.0f;
		for (int i = 0; i < s_Data.textureIndex; i++)
		{
			if (Asset::Equals(s_Data.textures[i], texture))
			{
				TexIndex = (float)i;
				break;
			}
		}

		if (
			s_Data.vertexIndex + 4 > MAX_QUAD_COUNT ||
			(TexIndex == -1.0f && s_Data.textureIndex == MAX_TEXTURE_UNIT)
		)
		{
			Flush();
		}

		if (TexIndex == -1.0f)
		{
			s_Data.textures[s_Data.textureIndex] = texture;
			TexIndex = (float)s_Data.textureIndex;
			s_Data.textureIndex++;
		}

		const glm::vec4 c(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);

		sX = sX / texture->GetWidth();
		sY = sY / texture->GetHeight();
		sW = sW / texture->GetWidth();
		sH = sH / texture->GetHeight();

		s_Data.buffer[s_Data.vertexIndex].Position = { dX     , dY      };
		s_Data.buffer[s_Data.vertexIndex].UV       = { sX     , sX      };
		s_Data.buffer[s_Data.vertexIndex].Color    = c;
		s_Data.buffer[s_Data.vertexIndex].TexIndex    = TexIndex;
		s_Data.vertexIndex++;

		s_Data.buffer[s_Data.vertexIndex].Position = { dX + dW, dY      };
		s_Data.buffer[s_Data.vertexIndex].UV       = { sX + sW, sX      };
		s_Data.buffer[s_Data.vertexIndex].Color    = c;
		s_Data.buffer[s_Data.vertexIndex].TexIndex    = TexIndex;
		s_Data.vertexIndex++;

		s_Data.buffer[s_Data.vertexIndex].Position = { dX     , dY + dH };
		s_Data.buffer[s_Data.vertexIndex].UV       = { sX     , sX + sH };
		s_Data.buffer[s_Data.vertexIndex].Color    = c;
		s_Data.buffer[s_Data.vertexIndex].TexIndex    = TexIndex;
		s_Data.vertexIndex++;

		s_Data.buffer[s_Data.vertexIndex].Position = { dX + dW, dY + dH };
		s_Data.buffer[s_Data.vertexIndex].UV       = { sX + sW, sX + sH };
		s_Data.buffer[s_Data.vertexIndex].Color    = c;
		s_Data.buffer[s_Data.vertexIndex].TexIndex    = TexIndex;
		s_Data.vertexIndex++;

		const glm::mat3& m = s_TransformStack.back();
		for (int i = 0; i < 4; i++)
		{
			Vertex& v = s_Data.buffer[s_Data.vertexIndex - i - 1];
			v.Position = m * glm::vec3(v.Position, 1.0f);
		}
	}

	void Renderer2D::PushState()
	{
		s_TransformStack.push_back(glm::mat3(1.0f));
	}

	void Renderer2D::PopState()
	{
		if (s_TransformStack.size() > 1) s_TransformStack.pop_back();
	}

	const glm::mat3& Renderer2D::GetTransform()
	{
		return s_TransformStack.back();
	}

	void Renderer2D::SetTransform(const glm::mat3& mat)
	{
		s_TransformStack.back() = mat;
	}

	void Renderer2D::Translate(float x, float y)
	{
		s_TransformStack.back() = glm::translate(s_TransformStack.back(), glm::vec2(x, y));
	}

	void Renderer2D::Scale(float x, float y)
	{
		s_TransformStack.back() = glm::scale(s_TransformStack.back(), glm::vec2(x, y));
	}

	void Renderer2D::Rotate(float r)
	{
		s_TransformStack.back() = glm::rotate(s_TransformStack.back(), r);
	}
}
