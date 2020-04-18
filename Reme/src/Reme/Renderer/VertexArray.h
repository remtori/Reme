#pragma once

#include "Reme/Renderer/Buffers.h"
#include "Reme/Core/AssetManager.h"

namespace Reme
{
	class VertexArray : public Asset
	{
	public:
		static Ref<VertexArray> Create();
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer> vertexBuf) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer> indexBuf) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
	};
}
