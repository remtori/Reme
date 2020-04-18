#pragma once

#include "Reme/Renderer/Color.h"
#include "Reme/Core/AssetManager.h"

namespace Reme
{
    class Image : public Asset
    {
    public:
        static Scope<Image> Create(uint32_t width, uint32_t height)
        {
            return CreateScope<Image>(width, height);
        }

        static Scope<Image> Create(const std::string& path)
        {
            return CreateScope<Image>(path);
        }
    public:
        Image(uint32_t width, uint32_t height);
        Image(const std::string& path);
        ~Image();

        inline uint32_t GetWidth() const { return m_Width; }
        inline uint32_t GetHeight() const { return m_Height; }

        inline Color GetPixel(uint32_t x, uint32_t y) const { return m_Pixels[x + y * m_Width]; }
        inline void SetPixel(uint32_t x, uint32_t y, const Color& color) { m_Pixels[x + y * m_Width] = color; }

        inline const std::vector<Color>& GetPixelsData() const { return m_Pixels; }
        inline void SetPixelsData(const Color* pixels)
        {
            memcpy(&m_Pixels[0], pixels, m_Width * m_Height);
        }

        inline void Copy(const Ref<Image>& source, uint32_t dX, uint32_t dY, bool applyAlpha = false)
        {
            Copy(source, dX, dY, 0, 0, source->GetWidth(), source->GetHeight(), applyAlpha);
        }

        inline void Copy(const Ref<Image>& source, uint32_t dX, uint32_t dY, uint32_t sX, uint32_t sY, bool applyAlpha = false)
        {
            Copy(source, dX, dY, sX, sY, source->GetWidth(), source->GetHeight(), applyAlpha);
        }

        void Copy(const Ref<Image>& source, uint32_t dX, uint32_t dY, uint32_t sX, uint32_t sY, uint32_t sW, uint32_t sH, bool applyAlpha = false);
    private:
        uint32_t m_Width, m_Height;
        std::vector<Color> m_Pixels;
    };
}
