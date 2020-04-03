#include "reme_pch.h"
#include "Impl/OpenGL/OpenGL_Buffers.h"

#include <glad/glad.h>

namespace Reme
{
	// VERTEX BUFFER
	OpenGL_VertexBuffer::OpenGL_VertexBuffer(uint32_t byteCount, bool isStatic)
	{
		glGenBuffers(1, &m_InternalID);
		glBindBuffer(GL_ARRAY_BUFFER, m_InternalID);
		glBufferData(GL_ARRAY_BUFFER, byteCount, nullptr, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}

	OpenGL_VertexBuffer::~OpenGL_VertexBuffer()
	{
		glDeleteBuffers(1, &m_InternalID);
	}

	void OpenGL_VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_InternalID);
	}

	void OpenGL_VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGL_VertexBuffer::SetData(float* data, uint32_t byteOffset, uint32_t byteCount)
	{
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, byteOffset, byteCount, data);
	}

	// INDEX BUFFER
	OpenGL_IndexBuffer::OpenGL_IndexBuffer(uint32_t byteCount, bool isStatic)
	{
		glGenBuffers(1, &m_InternalID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_InternalID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteCount * sizeof(uint32_t), nullptr, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}

	OpenGL_IndexBuffer::~OpenGL_IndexBuffer()
	{
		glDeleteBuffers(1, &m_InternalID);
	}

	void OpenGL_IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_InternalID);
	}

	void OpenGL_IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGL_IndexBuffer::SetData(uint32_t* data, uint32_t byteOffset, uint32_t byteCount)
	{
		Bind();
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, byteOffset, byteCount, data);
	}
}
