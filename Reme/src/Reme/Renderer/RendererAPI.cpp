#include "pch.h"
#include "Reme/Renderer/RendererAPI.h"

#include "Impl/OpenGL/OpenGL_RendererAPI.h"

namespace Reme
{
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
    RendererAPI* RenderCommand::s_RendererAPI = RendererAPI::Create();    

    RendererAPI* RendererAPI::Create()
    {
        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGL_RendererAPI();
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}
