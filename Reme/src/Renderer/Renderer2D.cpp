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

		glGenVertexArrays(1, &m_Data->VAO);
		glBindVertexArray(m_Data->VAO);

		glGenBuffers(1, &m_Data->vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_Data->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, 65535 * sizeof(float) * 5, nullptr, GL_DYNAMIC_DRAW);

		m_Data->flatShader = Shader::Create("Geometry Shader",
			// Vertex shader
			"#version 330 core\n"

			"uniform mat4 viewMat;\n"
			"uniform mat4 projMat;\n"

			"layout (location = 0) in vec3 Position;\n"
			"layout (location = 1) in vec2 UV;\n"

			"out vec2 Frag_UV;\n"
			"out vec3 Frag_Normal;\n"

			"void main()\n"
			"{\n"
			"	gl_Position = projMat * viewMat * vec4(Position, 1);\n"
			"	Frag_UV = vec2(UV.x, UV.y);\n"
			"}\n",
			// Fragment shader
			"#version 330 core\n"

			"uniform vec4 Color;\n"
			"uniform sampler2D Texture;\n"

			"in vec2 Frag_UV;\n"
			"layout(location = 0) out vec4 Frag_Color;\n"

			"void main()\n"
			"{\n"
			"    Frag_Color = Color * texture(Texture, Frag_UV);\n"
			"}\n"
		);

		m_Data->flatShader->Bind();
		m_Data->flatShader->SetInt("Texture", 0);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer2D::Shutdown()
	{
		delete m_Data;
	}

	void Renderer2D::Begin(Camera* cam)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(m_Data->VAO);
		m_Data->flatShader->Bind();
		m_Data->flatShader->SetMat4("viewMat", cam->GetViewMatrix());
		m_Data->flatShader->SetMat4("projMat", cam->GetProjectionMatrix());
	}

	void Renderer2D::End()
	{
		//GLenum err;
		//while ((err = glGetError()) != GL_NO_ERROR)
		//{
		//	LOG_ERROR("OpenGL Error: {}", err);
		//}
	}

	void Renderer2D::Draw(
		Texture* texture,
		glm::vec2 srcPos, glm::vec2 srcScale,
		glm::vec3 destPos, glm::vec2 destScale,
		glm::vec4 tintColor
	)
	{
		if (texture == 0) texture = m_Data->rgbTexture;
		else if (texture == (void*) 1) texture = m_Data->whiteTexture;

		float data[] = {
								// Position                                            // UV
			destPos.x              , destPos.y              , destPos.z,    srcPos.x             , srcPos.y,
			destPos.x + destScale.x, destPos.y              , destPos.z,    srcPos.x + srcScale.x, srcPos.y,
			destPos.x + destScale.x, destPos.y + destScale.y, destPos.z,    srcPos.x + srcScale.x, srcPos.y + srcScale.y,

			destPos.x              , destPos.y              , destPos.z,    srcPos.x             , srcPos.y,
			destPos.x              , destPos.y + destScale.y, destPos.z,    srcPos.x             , srcPos.y + srcScale.y,
			destPos.x + destScale.x, destPos.y + destScale.y, destPos.z,    srcPos.x + srcScale.x, srcPos.y + srcScale.y,
		};

		texture->Bind();
		m_Data->flatShader->SetFloat4("Color", tintColor);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(float) * 5, data);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
