#include "pch.h"
#include "Reme/Renderer/Buffers.h"
#include "Reme/Renderer/RendererAPI.h"

#include "Impl/OpenGL/OpenGL_Buffers.h"

namespace Reme
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t eleCount, bool isStatic)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateRef<OpenGL_VertexBuffer>(eleCount, isStatic);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t eleCount, bool isStatic)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateRef<OpenGL_IndexBuffer>(eleCount, isStatic);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
