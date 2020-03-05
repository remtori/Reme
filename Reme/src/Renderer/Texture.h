#pragma once

#include <string>

namespace Reme
{
    class Texture
    {
    public:
        static Texture* Create(uint32_t width, uint32_t height)
        {
            return new Texture(width, height);
        }
        static Texture* Create(const std::string& path)
        {
            return new Texture(path);
        }
    public:
        Texture(uint32_t width, uint32_t height);
        Texture(const std::string& path);
        ~Texture();

        inline uint32_t GetWidth() const { return m_Width;  }
        inline uint32_t GetHeight() const { return m_Height; }
        inline uint32_t GetInternalID() const { return m_TextureID; }

        void SetData(void* data, uint32_t size);

        void Bind(uint32_t slot = 0) const;
    private:
        uint32_t m_Width, m_Height;
        uint32_t m_TextureID;
        uint32_t m_InternalFormat, m_DataFormat;
    };
}
