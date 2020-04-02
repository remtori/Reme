#include "pch.h"
#include "Reme/Renderer2D/PixelTexture.h"

namespace Reme
{
    PixelTexture::PixelTexture(uint32_t width, uint32_t height)
        : m_Dirty(false), 
        m_Texture(Texture::Create(width, height)), 
        m_PixelData(width * height)
    {
    }

    PixelTexture::~PixelTexture()
    {
    }

    void PixelTexture::SetPixel(uint32_t x, uint32_t y, const Color& color)
    {
        uint32_t pos = x + y * GetWidth();        
        m_Dirty = m_PixelData.at(pos) != color;
        m_PixelData[pos] = color;
    }

    const Color& PixelTexture::GetPixel(uint32_t x, uint32_t y)
    {
        return m_PixelData[x * y * GetWidth()];
    }

    void PixelTexture::Bind(uint32_t slot = 0)
    {
        if (m_Dirty)
        {
            m_Dirty = false;
            m_Texture->SetData(m_PixelData.data());
        }

        m_Texture->Bind();
    }
}