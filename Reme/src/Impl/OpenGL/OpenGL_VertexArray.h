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
		void AddVertexBuffer(VertexBuffer* vertexBuf) override;
		void SetIndexBuffer(IndexBuffer* indexBuf) override;
	private:
		uint32_t m_InternalID;
		uint32_t m_VertexBufferIndex;
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer;
	};
}
