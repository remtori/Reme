#include "RemePCH.h"
#include "Reme/Renderer/Texture.h"
#include "Reme/Renderer/RendererAPI.h"
#include "Reme/Core/Core.h"

#ifdef TEST
#include "Impl/Test/Test_Texture.h"
#endif
#include "Impl/OpenGL/OpenGL_Texture.h"

namespace Reme
{
	Ref<Texture> Texture::Default;
	Ref<Texture> Texture::White;

	void Texture::Init()
	{
		PROFILE_FUNCTION();

		Texture::Default = Texture::Create(2, 2);
        Color rgbTextureData[] = { Color::Red, Color::Green, Color::Blue, Color::White };
        Texture::Default->SetData(rgbTextureData);
		// Texture::Default->GenerateMipmap();

		Texture::White = Texture::Create(1, 1);
        Texture::White->SetData(&Color::White);
		// Texture::White->GenerateMipmap();
	}

    Ref<Texture> Texture::Create(uint32_t width, uint32_t height)
    {
		PROFILE_FUNCTION();

        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: CORE_ASSERT(false, "RendererAPI::None is not supported!"); return Texture::Default;
			case RendererAPI::OpenGL: return AssetManager::Create<OpenGL_Texture>(width, height);
#ifdef TEST
			case RendererAPI::Test: return AssetManager::Create<Test_Texture>(width, height);
#endif
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return Texture::Default;
    }

	Ref<Texture> Texture::Create(const Ref<Image>& image)
	{
		PROFILE_FUNCTION();

		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: CORE_ASSERT(false, "RendererAPI::None is not supported!"); return Texture::Default;
			case RendererAPI::OpenGL: return AssetManager::Create<OpenGL_Texture>(image);
#ifdef TEST
			case RendererAPI::Test: return AssetManager::Create<Test_Texture>(image);
#endif
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return Texture::Default;
	}

    Ref<Texture> Texture::Create(const std::string& path)
    {
		PROFILE_FUNCTION();
		
		// Create Texture from a path might fail
		// TODO: Solve this
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: CORE_ASSERT(false, "RendererAPI::None is not supported!"); return Texture::Default;
			case RendererAPI::OpenGL: return AssetManager::Create<OpenGL_Texture>(Image::Create(path));
#ifdef TEST
			case RendererAPI::Test: return AssetManager::Create<Test_Texture>(Image::Create(path));
#endif
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return Texture::Default;
    }
}
