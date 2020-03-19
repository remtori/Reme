#pragma once

#include "Renderer/Buffers.h"

namespace Reme
{
	class VertexArray
	{
	public:
		static VertexArray* Create()
		{
			return new VertexArray();
		}
	private:
		VertexArray();
	public:
		~VertexArray();
		void Bind();
		void Unbind();
		void AddVertexBuffer(VertexBuffer* vertexBuf);
		void SetIndexBuffer(IndexBuffer* indexBuf);
	private:
		uint32_t m_InternalID;
		uint32_t m_VertexBufferIndex;
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer;
	};
}
