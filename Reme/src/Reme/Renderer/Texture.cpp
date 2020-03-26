#include "pch.h"
#include "Reme/Renderer/Texture.h"
#include "Reme/Renderer/RendererAPI.h"

#include "Impl/OpenGL/OpenGL_Texture.h"

namespace Reme
{
    Texture* Texture::Create(uint32_t width, uint32_t height)
    {
        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGL_Texture(width, height);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }

    Texture* Texture::Create(const std::string& path)
    {
        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGL_Texture(path);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}
