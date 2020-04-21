#include "RemePCH.h"
#include "Reme/Renderer/VertexArray.h"
#include "Reme/Renderer/RendererAPI.h"

#ifdef TEST
#include "Impl/Test/Test_VertexArray.h"
#endif
#include "Impl/OpenGL/OpenGL_VertexArray.h"

namespace Reme
{
	Ref<VertexArray> VertexArray::Create()
	{
		PROFILE_FUNCTION();	
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateRef<OpenGL_VertexArray>();
#ifdef TEST
			case RendererAPI::Test: return CreateRef<Test_VertexArray>();
#endif
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
