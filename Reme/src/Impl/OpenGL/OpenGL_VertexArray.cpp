#include "RemePCH.h"
#include "Impl/OpenGL/OpenGL_VertexArray.h"
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

		CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGL_VertexArray::OpenGL_VertexArray()
		: m_VertexBufferIndex(0)
	{
		glGenVertexArrays(1, &m_InternalID);
	}

	OpenGL_VertexArray::~OpenGL_VertexArray()
	{
		glDeleteVertexArrays(1, &m_InternalID);
	}

	void OpenGL_VertexArray::Bind()
	{
		glBindVertexArray(m_InternalID);
	}

	void OpenGL_VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void OpenGL_VertexArray::AddVertexBuffer(Ref<VertexBuffer> buf)
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

	void OpenGL_VertexArray::SetIndexBuffer(Ref<IndexBuffer> buf)
	{
		Bind();
		buf->Bind();
		m_IndexBuffer = buf;
		Unbind();
	}
}
