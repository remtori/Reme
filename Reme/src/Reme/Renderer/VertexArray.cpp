#include "RemePCH.h"
#include "Reme/Renderer/VertexArray.h"
#include "Reme/Renderer/RendererAPI.h"

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
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
