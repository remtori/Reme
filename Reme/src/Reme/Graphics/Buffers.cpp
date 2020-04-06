#include "reme_pch.h"
#include "Reme/Graphics/Buffers.h"
#include "Reme/Graphics/RendererAPI.h"

#include "Impl/OpenGL/OpenGL_Buffers.h"

namespace Reme
{
	Scope<VertexBuffer> VertexBuffer::Create(uint32_t eleCount, bool isStatic)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateScope<OpenGL_VertexBuffer>(eleCount, isStatic);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Scope<IndexBuffer> IndexBuffer::Create(uint32_t eleCount, bool isStatic)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateScope<OpenGL_IndexBuffer>(eleCount, isStatic);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
