#include "RemePCH.h"
#include "Reme/Renderer/BitmapTexture.h"
#include "Reme/Renderer/Texture.h"

namespace Reme
{
    BitmapTexture::BitmapTexture(uint32_t width, uint32_t height)
    {
        m_Image = Image::Create(width, height);
        m_Texture = Texture::Create(width, height);
    }

    BitmapTexture::BitmapTexture(const Ref<Image>& image)
    {
        m_Image = Image::Create(image->GetWidth(), image->GetHeight());
        m_Image->SetPixelsData(image->GetPixelsData().data());
        m_Texture = Texture::Create(image);
    }

    BitmapTexture::BitmapTexture(const std::string& path)
    {
        m_Image = Image::Create(path);
        m_Texture = Texture::Create(m_Image);
    }

    BitmapTexture::~BitmapTexture()
    {

    }

    void BitmapTexture::SetPixel(uint32_t x, uint32_t y, const Color& color)
    {
        if (GetPixel(x, y) == color) return;

        m_Image->SetPixel(x, y, color);
        m_Dirty = true;
        m_DirtyArea.x = std::min(x, m_DirtyArea.x);
        m_DirtyArea.y = std::min(y, m_DirtyArea.y);
        m_DirtyArea.z = std::max(x, m_DirtyArea.z);
        m_DirtyArea.w = std::max(y, m_DirtyArea.w);
    }

    void BitmapTexture::SetPixelsData(const Color* pixels)
    {
        m_Image->SetPixelsData(pixels);        
        m_Dirty = true;
        m_DirtyArea.x = 0;
        m_DirtyArea.y = 0;
        m_DirtyArea.z = GetWidth();
        m_DirtyArea.w = GetHeight();
    }    

    void BitmapTexture::Resize(uint32_t width, uint32_t height)
    {

    }

    void BitmapTexture::Bind(uint32_t slot)
    {
        PROFILE_FUNCTION();

        m_Texture->Bind(slot);

        if (!m_Dirty)
            return;

        m_Dirty = false;
        uint32_t minX = m_DirtyArea.x;
        uint32_t minY = m_DirtyArea.y;
        uint32_t maxX = m_DirtyArea.z;
        uint32_t maxY = m_DirtyArea.w;
        const Color* pixels = m_Image->GetPixelsData().data();

        if (minX == 0 && minY == 0 && maxX == GetWidth() && maxY == GetHeight())
        {
            m_Texture->SetData(pixels);
            return;
        }

        uint32_t width = GetWidth();
        if (minX == 0 && maxX == width)
        {
            m_Texture->SetData(&pixels[minY * width], 0, minY, width, maxY - minY + 1);
        }

        uint32_t offset = 0;
        uint32_t strideLen = maxX - minX + 1;
        Color* buffer = new Color[strideLen * (maxY - minY + 1)];

        for (uint32_t y = minY; y <= maxY; ++y)
        {
            memcpy(&buffer[offset], &pixels[minX + y * width], strideLen);
            offset += strideLen;
        }

        m_Texture->SetData(buffer, minX, minY, maxX - minX + 1, maxY - minY + 1);
        delete[] buffer;
    }    
}
