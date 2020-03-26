#include "pch.h"
#include "Reme/Renderer/Renderer2D.h"
#include "Reme/Renderer/RendererAPI.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Reme
{
	Renderer2DData* Renderer2D::m_Data;

	void Renderer2D::Init()
	{
		m_Data = new Renderer2DData();

		m_Data->whiteTexture = Texture::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		m_Data->whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		m_Data->rgbTexture = Texture::Create(2, 2);
		uint32_t rgbTextureData[] = { 0xff0000ff, 0xff00ff00, 0xffff0000, 0xffffffff };
		m_Data->rgbTexture->SetData(&rgbTextureData, sizeof(rgbTextureData));		

		m_Data->flatShader = Shader::Create("Flat Shader",
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

		m_Data->flatShader->Bind();
		m_Data->flatShader->SetInt("Texture", 0);
	
		m_Data->VBO = VertexBuffer::Create(MAX_VERTEX_BUFFER_SIZE, false);
		m_Data->VBO->SetLayout({
			{ ShaderDataType::Float2, "Position" },
			{ ShaderDataType::Float2, "UV" },			
			{ ShaderDataType::Float4, "Color" },
		});		

		m_Data->VAO = VertexArray::Create();
		m_Data->VAO->AddVertexBuffer(m_Data->VBO);
		RenderCommand::SetClearColor(Color(0xffffff));
	}

	void Renderer2D::Shutdown()
	{		
		delete m_Data->flatShader;
		delete m_Data->whiteTexture;
		delete m_Data->rgbTexture;
		delete m_Data->VBO;
		delete m_Data->VAO;
		delete m_Data;
	}

	void Renderer2D::Begin(Camera* cam)
	{
		RenderCommand::Clear();
		m_Data->flatShader->Bind();
		m_Data->flatShader->SetMat4("viewMat", cam->GetViewMatrix());
		m_Data->flatShader->SetMat4("projMat", cam->GetProjectionMatrix());
		m_Data->drawables.clear();
		m_Data->VAO->Bind();
	}

	void Renderer2D::End()
	{
		Flush();		
		m_Data->VAO->Unbind();
	}

	void Renderer2D::Flush()
	{
		static float* buffer = new float[MAX_VERTEX_BUFFER_SIZE];

		if (m_Data->drawables.empty()) return;

		uint32_t vertexCount = 0;
		Texture* currentTexture = m_Data->drawables[0].texture;

		auto draw = [&]() {
			currentTexture->Bind();
			m_Data->VBO->SetData(buffer, 0, vertexCount * FLOAT_PER_VERTEX);
			RenderCommand::DrawArrays(vertexCount, 0);
			vertexCount = 0;
		};

		uint8_t i;
		for (Drawable& d : m_Data->drawables)
		{
			if (currentTexture != d.texture)
			{
				draw();
				currentTexture = d.texture;
			}

			for (i = 0; i < VERTEX_PER_DRAWABLE; i++)
			{
				// Fill first 4 float: X, Y, U, V
				memcpy(&buffer[vertexCount * FLOAT_PER_VERTEX], &d.vertexArray[i], sizeof(Vertex));

				// Fill the color attrib
				buffer[vertexCount * FLOAT_PER_VERTEX + 4] = d.color.r / 255.0f;
				buffer[vertexCount * FLOAT_PER_VERTEX + 5] = d.color.g / 255.0f;
				buffer[vertexCount * FLOAT_PER_VERTEX + 6] = d.color.b / 255.0f;
				buffer[vertexCount * FLOAT_PER_VERTEX + 7] = d.color.a / 255.0f;

				vertexCount++;
			}
		}		

		draw();
	}

	void Renderer2D::Draw(
		Texture* texture,
		glm::vec2 sP, glm::vec2 sS,
		glm::vec2 dP, glm::vec2 dS,
		Color color
	)
	{
		if (texture == 0) texture = m_Data->rgbTexture;
		else if (texture == (void*) 1) texture = m_Data->whiteTexture;

		float c[4] = { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };
		Drawable r = {
				color,
				texture,
				{
					{ dP.x       , dP.y       , sP.x       , sP.y        },
					{ dP.x + dS.x, dP.y       , sP.x + sS.x, sP.y        },
					{ dP.x       , dP.y + dS.y, sP.x       , sP.y + sS.y },
					{ dP.x + dS.x, dP.y       , sP.x + sS.x, sP.y        },
					{ dP.x       , dP.y + dS.y, sP.x       , sP.y + sS.y },
					{ dP.x + dS.x, dP.y + dS.y, sP.x + sS.x, sP.y + sS.y },
				}
		};

		m_Data->drawables.push_back(r);
		if (m_Data->drawables.size() > MAX_DRAWABLE_PER_BATCH) Flush();
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
