#include "RemePCH.h"
#include "Impl/Test/Test_VertexArray.h"
#include "Reme/Renderer/ShaderDataLayout.h"

namespace Reme
{
	uint32_t Test_VertexArray::BindedVAO = 0;

	Test_VertexArray::Test_VertexArray()
		: m_VertexBufferIndex(0)
	{
	}

	Test_VertexArray::~Test_VertexArray()
	{
	}

	void Test_VertexArray::AddVertexBuffer(Ref<VertexBuffer> buf)
	{
		const auto& layout = buf->GetLayout();
		for (const auto& element : layout)
		{
			// TODO: Dump/Store these somehow

			// glEnableVertexAttribArray(m_VertexBufferIndex);
			// glVertexAttribPointer(
			// 	m_VertexBufferIndex,
			// 	element.GetComponentCount(),
			// 	ShaderDataTypeToOpenGLBaseType(element.Type),
			// 	element.Normalized ? GL_TRUE : GL_FALSE,
			// 	layout.GetStride(),
			// 	(const void*) element.Offset
			// );
			// glVertexAttribDivisor(m_VertexBufferIndex, element.Divisor);

			m_VertexBufferIndex++;
		}
		m_VertexBuffers.push_back(buf);
	}

	void Test_VertexArray::SetIndexBuffer(Ref<IndexBuffer> buf)
	{
		m_IndexBuffer = buf;
	}
}
