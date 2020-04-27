#include "RemePCH.h"
#include "Impl/Test/Test_Buffers.h"

namespace Reme
{
	uint32_t Test_VertexBuffer::BindedVBO = 0;
	uint32_t Test_IndexBuffer::BindedIBO = 0;

	Test_VertexBuffer::Test_VertexBuffer(uint32_t byteCount, bool isStatic)
	{
		m_Data.resize(byteCount / sizeof(float));
	}

	Test_VertexBuffer::~Test_VertexBuffer()
	{
	}

	void Test_VertexBuffer::SetData(float* data, uint32_t byteOffset, uint32_t byteCount)
	{
		memcpy(&m_Data[byteOffset / sizeof(float)], data, byteCount);
	}

	Test_IndexBuffer::Test_IndexBuffer(uint32_t byteCount, bool isStatic)
	{
		m_Data.resize(byteCount / sizeof(uint32_t));
	}

	Test_IndexBuffer::~Test_IndexBuffer()
	{
	}

	void Test_IndexBuffer::SetData(uint32_t* data, uint32_t byteOffset, uint32_t byteCount)
	{
		memcpy(&m_Data[byteOffset / sizeof(uint32_t)], data, byteCount);
	}
}
