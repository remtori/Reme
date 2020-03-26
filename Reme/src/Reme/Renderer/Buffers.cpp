#include "pch.h"
#include "Reme/Renderer/Buffers.h"
#include "Reme/Renderer/RendererAPI.h"

#include "Impl/OpenGL/OpenGL_Buffers.h"

namespace Reme
{
	VertexBuffer* VertexBuffer::Create(uint32_t eleCount, bool isStatic)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGL_VertexBuffer(eleCount, isStatic);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t eleCount, bool isStatic)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGL_IndexBuffer(eleCount, isStatic);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
