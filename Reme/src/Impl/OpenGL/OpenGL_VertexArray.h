#pragma once

#include "Reme/Renderer/VertexArray.h"

namespace Reme
{
	class OpenGL_VertexArray : public VertexArray
	{
	public:
		OpenGL_VertexArray();
		~OpenGL_VertexArray();
		void Bind() override;
		void Unbind() override;

		void AddVertexBuffer(Ref<VertexBuffer> vertexBuf) override;
		void SetIndexBuffer(Ref<IndexBuffer> indexBuf) override;

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
	private:
		uint32_t m_InternalID;
		uint32_t m_VertexBufferIndex;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}
