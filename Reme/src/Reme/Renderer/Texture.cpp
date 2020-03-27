#include "pch.h"
#include "Reme/Renderer/Texture.h"
#include "Reme/Renderer/RendererAPI.h"

#include "Impl/OpenGL/OpenGL_Texture.h"

namespace Reme
{
	Ref<Texture> Texture::Default;
	Ref<Texture> Texture::White;

	void Texture::Init()
	{
		Texture::Default = Texture::Create(2, 2);
        uint32_t rgbTextureData[] = { 0xff0000ff, 0xff00ff00, 0xffff0000, 0xffffffff };
        Texture::Default->SetData(&rgbTextureData, sizeof(rgbTextureData));
        
		Texture::White = Texture::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        Texture::White->SetData(&whiteTextureData, sizeof(uint32_t));
	}

    Ref<Texture> Texture::Create(uint32_t width, uint32_t height)
    {
        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateRef<OpenGL_Texture>(width, height);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }

    Ref<Texture> Texture::Create(const std::string& path)
    {
		// Create Texture from a path might fail
		// in that case we return a nullptr instead of a corrupted texture
		// TODO: Solve this using texture atlas
		try
		{
			switch (RendererAPI::GetAPI())
			{
				case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
				case RendererAPI::OpenGL: return CreateRef<OpenGL_Texture>(path);
			}
		}
		catch (int e)
		{
			return nullptr;
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}
