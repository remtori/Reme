#include "RemePCH.h"
#include "Reme/Renderer/RendererAPI.h"

#ifdef TEST
#include "Impl/Test/Test_RendererAPI.h"
#endif
#include "Impl/OpenGL/OpenGL_RendererAPI.h"

namespace Reme
{
    
#ifdef TEST_RENDERAPI
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::Test;
#else
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
#endif

    RendererAPI* RenderCommand::s_RendererAPI = RendererAPI::Create();

    RendererAPI* RendererAPI::Create()
    {
        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGL_RendererAPI();
#ifdef TEST
            case RendererAPI::Test: return new Test_RendererAPI();
#endif
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}
