#pragma once

#include "Reme/Renderer/Buffers.h"

namespace Reme
{
	class VertexArray
	{
	public:
		static VertexArray* Create();
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(VertexBuffer* vertexBuf) = 0;
		virtual void SetIndexBuffer(IndexBuffer* indexBuf) = 0;

		virtual const std::vector<VertexBuffer*>& GetVertexBuffers() const = 0;
		virtual const IndexBuffer* GetIndexBuffer() const = 0;
	};
}
