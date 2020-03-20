#pragma once

#include "Renderer/ShaderDataLayout.h"

namespace Reme
{
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(uint32_t eleCount, bool isStatic = true)
		{
			return new VertexBuffer(eleCount, isStatic);
		}
	private:
		VertexBuffer(uint32_t eleCount, bool isStatic);
	public:
		~VertexBuffer();
		void Bind();
		void SetData(float* data, uint32_t eleOffset, uint32_t eleCount);

		const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
	private:
		uint32_t m_InternalID;
		BufferLayout m_Layout;
	};


	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(uint32_t eleCount, bool isStatic = true)
		{
			return new IndexBuffer(eleCount, isStatic);
		}
	private:
		IndexBuffer(uint32_t eleCount, bool isStatic);
	public:
		~IndexBuffer();
		void Bind();
		void SetData(uint32_t* data, uint32_t eleOffset, uint32_t eleCount);
	private:
		uint32_t m_InternalID;
	};
}

