#include "pch.h"
#include "Reme/Renderer/VertexArray.h"
#include "Reme/Renderer/RendererAPI.h"

#include "Impl/OpenGL/OpenGL_VertexArray.h"

namespace Reme
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateRef<OpenGL_VertexArray>();
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
