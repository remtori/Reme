#include "reme_pch.h"
#include "Reme/Graphics/Texture.h"
#include "Reme/Graphics/RendererAPI.h"
#include "Reme/Core/Core.h"

#include "Impl/OpenGL/OpenGL_Texture.h"

namespace Reme
{
	Ref<Texture> Texture::Default;
	Ref<Texture> Texture::White;

	void Texture::Init()
	{
		Texture::Default = Texture::Create(2, 2);
        Color rgbTextureData[] = { Color::Red, Color::Green, Color::Blue, Color::White };
        Texture::Default->SetData(rgbTextureData);
		// Texture::Default->GenerateMipmap();

		Texture::White = Texture::Create(1, 1);
        Texture::White->SetData(&Color::White);
		// Texture::White->GenerateMipmap();
	}

    Scope<Texture> Texture::Create(uint32_t width, uint32_t height)
    {
        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateScope<OpenGL_Texture>(width, height);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }

	Scope<Texture> Texture::Create(const Ref<Image>& image)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateScope<OpenGL_Texture>(image);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

    Scope<Texture> Texture::Create(const std::string& path)
    {
		// Create Texture from a path might fail
		// TODO: Solve this
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateScope<OpenGL_Texture>(Image::Create(path));
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}
