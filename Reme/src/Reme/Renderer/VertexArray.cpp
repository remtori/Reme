#include "pch.h"
#include "Reme/Renderer/VertexArray.h"
#include "Reme/Renderer/ShaderDataLayout.h"

#include <glad/glad.h>

namespace Reme
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		}

		ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	VertexArray::VertexArray()
		: m_VertexBufferIndex(0)
	{
		glGenVertexArrays(1, &m_InternalID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_InternalID);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_InternalID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(VertexBuffer* buf)
	{
		Bind();
		buf->Bind();
		const auto& layout = buf->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(
				m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*) element.Offset
			);
			glVertexAttribDivisor(m_VertexBufferIndex, element.Divisor);

			m_VertexBufferIndex++;
		}
		m_VertexBuffers.push_back(buf);
		Unbind();
	}

	void VertexArray::SetIndexBuffer(IndexBuffer* buf)
	{
		Bind();
		buf->Bind();
		m_IndexBuffer = buf;
		Unbind();
	}
}
