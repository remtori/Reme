#pragma once

#include "Reme/Graphics/Buffers.h"
#include "Reme/Graphics/ShaderDataLayout.h"

namespace Reme
{
	class OpenGL_VertexBuffer : public VertexBuffer
	{
	public:
		OpenGL_VertexBuffer(uint32_t byteCount, bool isStatic);
		~OpenGL_VertexBuffer();
		void Bind() override;
		void Unbind() override;
		void SetData(float* data, uint32_t byteOffset, uint32_t byteCount) override;
	private:
		uint32_t m_InternalID;
	};


	class OpenGL_IndexBuffer : public IndexBuffer
	{
	public:
		OpenGL_IndexBuffer(uint32_t byteCount, bool isStatic);
		~OpenGL_IndexBuffer();
		void Bind() override;
		void Unbind() override;
		void SetData(uint32_t* data, uint32_t byteOffset, uint32_t byteCount) override;
	private:
		uint32_t m_InternalID;
	};
}

