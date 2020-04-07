#include "reme_pch.h"
#include "Reme/Graphics/VertexArray.h"
#include "Reme/Graphics/RendererAPI.h"

#include "Impl/OpenGL/OpenGL_VertexArray.h"

namespace Reme
{
	Scope<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateScope<OpenGL_VertexArray>();
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}