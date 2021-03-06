#pragma once

#include "Reme/Renderer/Texture.h"
#include "Reme/Renderer/Image.h"

namespace Reme
{
    class OpenGL_Texture : public Texture
    {
    public:
        OpenGL_Texture(uint32_t width, uint32_t height);
        OpenGL_Texture(const Ref<Image>& image);
        ~OpenGL_Texture();

        inline uint32_t GetWidth() const override { return m_Width;  }
        inline uint32_t GetHeight() const override { return m_Height; }
        inline uint32_t GetInternalID() const override { return m_TextureID; }

        void GenerateMipmap() const override;
        void SetData(const Color* data, uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        void Bind(uint32_t slot) override;
    private:
        uint32_t m_Width, m_Height;
        uint32_t m_TextureID;
    };
}
