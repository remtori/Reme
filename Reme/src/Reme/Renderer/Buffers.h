#pragma once

#include "Reme/Renderer/ShaderDataLayout.h"
#include "Reme/Core/AssetManager.h"

namespace Reme
{
	class VertexBuffer : public Asset
	{
	public:
		static Ref<VertexBuffer> Create(uint32_t byteCount, bool isStatic = true);
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetData(float* data, uint32_t byteOffset, uint32_t byteCount) = 0;

		const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
	private:
		BufferLayout m_Layout;
	};

	class IndexBuffer : public Asset
	{
	public:
		static Ref<IndexBuffer> Create(uint32_t byteCount, bool isStatic = true);
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetData(uint32_t* data, uint32_t byteOffset, uint32_t byteCount) = 0;
	};
}

