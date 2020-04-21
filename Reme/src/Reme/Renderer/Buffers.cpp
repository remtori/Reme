#include "RemePCH.h"
#include "Reme/Renderer/Buffers.h"
#include "Reme/Renderer/RendererAPI.h"

#ifdef TEST
#include "Impl/Test/Test_Buffers.h"
#endif
#include "Impl/OpenGL/OpenGL_Buffers.h"

namespace Reme
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t eleCount, bool isStatic)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateRef<OpenGL_VertexBuffer>(eleCount, isStatic);
#ifdef TEST
			case RendererAPI::Test: return CreateRef<Test_VertexBuffer>(eleCount, isStatic);
#else
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
#endif
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t eleCount, bool isStatic)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateRef<OpenGL_IndexBuffer>(eleCount, isStatic);		
#ifdef TEST
			case RendererAPI::Test: return CreateRef<Test_IndexBuffer>(eleCount, isStatic);
#endif
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
