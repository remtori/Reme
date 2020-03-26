#pragma once

#include "Reme/Renderer/Texture.h"
#include <string>

namespace Reme
{
    class OpenGL_Texture : public Texture
    {
    public:
        OpenGL_Texture(uint32_t width, uint32_t height);
        OpenGL_Texture(const std::string& path);
    public:
        ~OpenGL_Texture();

        inline uint32_t GetWidth() const override { return m_Width;  }
        inline uint32_t GetHeight() const override { return m_Height; }
        inline uint32_t GetInternalID() const override { return m_TextureID; }

        void SetData(void* data, uint32_t size) override;

        void Bind(uint32_t slot) const override;
    private:
        uint32_t m_Width, m_Height;
        uint32_t m_TextureID;
        uint32_t m_InternalFormat, m_DataFormat;
    };
}
