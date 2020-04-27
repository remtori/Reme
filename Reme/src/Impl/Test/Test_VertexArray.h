#pragma once

#include "Reme/Renderer/VertexArray.h"

namespace Reme
{
	class Test_VertexArray : public VertexArray
	{
	public:
		static uint32_t BindedVAO;

		Test_VertexArray();
		~Test_VertexArray();
		void Bind() override;
		void Unbind() override { BindedVAO = 0; }
		bool IsBinded() { return BindedVAO == GetAssetID(); }

		void AddVertexBuffer(Ref<VertexBuffer> vertexBuf) override;
		void SetIndexBuffer(Ref<IndexBuffer> indexBuf) override;

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
	private:
		uint32_t m_VertexBufferIndex;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}
