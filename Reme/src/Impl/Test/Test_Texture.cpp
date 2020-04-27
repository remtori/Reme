#include "RemePCH.h"
#include "Impl/Test/Test_Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Reme
{
    uint32_t Test_Texture::BindedTexture;

    Test_Texture::Test_Texture(uint32_t width, uint32_t height)
        : m_Width(width)
        , m_Height(height)
    {                
        m_Data.resize(width * height, Color::Black);
    }

    Test_Texture::Test_Texture(const Ref<Image>& img)
        : m_Width(img->GetWidth())
        , m_Height(img->GetHeight())
    {
        m_Data.resize(m_Width * m_Height, Color::Black);
    }

    Test_Texture::~Test_Texture()
    {
    }

    void Test_Texture::SetData(const Color* data, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        if (width == 0) width = m_Width;
        if (height == 0) height = m_Height;

        for (uint32_t i = y; i < height; ++i)
        {
            memcpy(&m_Data[x + m_Width * i], &data[i * width], width);
        }
    }
}
