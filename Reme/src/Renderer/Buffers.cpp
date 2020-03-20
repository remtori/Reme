#include "pch.h"
#include "Renderer/Buffers.h"

#include <glad/glad.h>

namespace Reme
{
	// VERTEX BUFFER
	VertexBuffer::VertexBuffer(uint32_t eleCount, bool isStatic)
	{
		glGenBuffers(1, &m_InternalID);
		glBindBuffer(GL_ARRAY_BUFFER, m_InternalID);
		glBufferData(GL_ARRAY_BUFFER, eleCount * sizeof(float), nullptr, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_InternalID);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_InternalID);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::SetData(float* data, uint32_t eleOffset, uint32_t eleCount)
	{
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, eleOffset * sizeof(float), eleCount * sizeof(float), data);
	}

	// INDEX BUFFER
	IndexBuffer::IndexBuffer(uint32_t eleCount, bool isStatic)
	{
		glGenBuffers(1, &m_InternalID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_InternalID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, eleCount * sizeof(uint32_t), nullptr, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_InternalID);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_InternalID);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::SetData(uint32_t* data, uint32_t eleOffset, uint32_t eleCount)
	{
		Bind();
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, eleOffset * sizeof(uint32_t), eleCount * sizeof(uint32_t), data);
	}
}
