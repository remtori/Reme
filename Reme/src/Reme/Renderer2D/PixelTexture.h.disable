#pragma once

#include "Reme/Renderer/Texture.h"

#include <vector>

namespace Reme
{
    class PixelTexture : public Texture
    {
    public:
        PixelTexture(uint32_t width, uint32_t height);
        ~PixelTexture();

        void SetPixel(uint32_t x, uint32_t y, const Color& color);
        const Color& GetPixel(uint32_t x, uint32_t y);

        inline uint32_t GetWidth() const override { return m_Texture->GetWidth(); }
        inline uint32_t GetHeight() const override { return m_Texture->GetHeight(); }
        inline uint32_t GetInternalID() const override { return m_Texture->GetInternalID(); }

        void SetData(const Color* data, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            throw "Do Not Use!";
        }

        void Bind(uint32_t slot = 0) override;
    private:
        Scope<Texture> m_Texture;
        std::vector<Color> m_PixelData;
        bool m_Dirty;
    };
}
