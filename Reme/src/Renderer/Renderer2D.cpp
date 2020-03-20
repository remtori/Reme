#include "pch.h"
#include "Renderer/Renderer2D.h"

#include <glad/glad.h>
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

		m_Data->flatShader = Shader::Create("Geometry Shader",
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
			"	gl_Position = projMat * viewMat * vec4(Position, 0, 1);\n"
			"	Frag_UV = UV;\n"
			"   Frag_Color = Color;"
			"}\n",
			// Fragment shader
			"#version 330 core\n"

			"uniform sampler2D Texture;\n"

			"in vec2 Frag_UV;\n"
			"in vec4 Frag_Color;\n"
			"layout(location = 0) out vec4 Out_Color;\n"

			"void main()\n"
			"{\n"
			"    Out_Color = Frag_Color * texture(Texture, Frag_UV);\n"
			"}\n"
		);

		m_Data->flatShader->Bind();
		m_Data->flatShader->SetInt("Texture", 0);

		m_Data->VAO = VertexArray::Create();
		m_Data->vertexBuffer = VertexBuffer::Create(MAX_VERTEX_SIZE);
		m_Data->buffer = new float[MAX_VERTEX_SIZE];
		m_Data->vertexBuffer->SetLayout({
			{ ShaderDataType::Float2, "Position" },
			{ ShaderDataType::Float2, "UV" },
			{ ShaderDataType::Float4, "Color" },
		});

		m_Data->VAO->AddVertexBuffer(m_Data->vertexBuffer);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Renderer2D::Shutdown()
	{		
		delete m_Data->flatShader;
		delete m_Data->whiteTexture;
		delete m_Data->rgbTexture;
		delete m_Data->VAO;
		delete m_Data->vertexBuffer;
		delete m_Data->buffer;
		delete m_Data;
	}

	void Renderer2D::Begin(Camera* cam)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		m_Data->VAO->Bind();
		m_Data->flatShader->Bind();
		m_Data->flatShader->SetMat4("viewMat", cam->GetViewMatrix());
		m_Data->flatShader->SetMat4("projMat", cam->GetProjectionMatrix());
		m_Data->elements.clear();
	}

	void Renderer2D::End()
	{
		Flush();

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			LOG_ERROR("OpenGL Error: {}", err);
		}
	}

	void Renderer2D::Flush()
	{
		if (m_Data->elements.empty()) return;

		Texture* currTex = m_Data->elements[0].texture;
		uint32_t offset = 0;

		for (Drawable& d : m_Data->elements)
		{
			if (currTex != d.texture)
			{
				currTex->Bind();
				m_Data->vertexBuffer->SetData(m_Data->buffer, 0, offset * FLOAT_PER_VERTEX);
				glDrawArrays(GL_TRIANGLES, 0, offset);

				offset = 0;
				currTex = d.texture;
			}

			memcpy(&m_Data->buffer[offset * FLOAT_PER_VERTEX], &d.vertexArray[0], sizeof(d.vertexArray));
			offset += VERTEX_PER_DRAWABLE;
		}

		currTex->Bind();
		m_Data->vertexBuffer->SetData(m_Data->buffer, 0, offset * FLOAT_PER_VERTEX);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, offset);

		m_Data->elements.clear();
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
				texture,
				{
					{ dP.x       , dP.y       , sP.x       , sP.y       , c[0], c[1], c[2], c[3] },
					{ dP.x + dS.x, dP.y       , sP.x + sS.x, sP.y       , c[0], c[1], c[2], c[3] },
					{ dP.x       , dP.y + dS.y, sP.x       , sP.y + sS.y, c[0], c[1], c[2], c[3] },
					{ dP.x + dS.x, dP.y       , sP.x + sS.x, sP.y       , c[0], c[1], c[2], c[3] },
					{ dP.x       , dP.y + dS.y, sP.x       , sP.y + sS.y, c[0], c[1], c[2], c[3] },
					{ dP.x + dS.x, dP.y + dS.y, sP.x + sS.x, sP.y + sS.y, c[0], c[1], c[2], c[3] },
				}
		};

		m_Data->elements.push_back(r);
		if (m_Data->elements.size() > 1000) Flush();
	}
}
