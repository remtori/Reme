#include "reme_pch.h"
#include "Impl/OpenGL/OpenGL_Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Reme
{
    bool isPowerOf2(uint32_t x) {
        return (x & (x - 1)) == 0;
    }

    OpenGL_Texture::OpenGL_Texture(uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height)
    {
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGL_Texture::OpenGL_Texture(const Ref<Image>& img)
        : m_Width(img->GetWidth()), m_Height(img->GetHeight())
    {
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &img->GetPixelsData()[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        GenerateMipmap();
    }

    OpenGL_Texture::~OpenGL_Texture()
    {
        glDeleteTextures(1, &m_TextureID);
    }

    void OpenGL_Texture::GenerateMipmap() const
    {        
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        if (isPowerOf2(m_Width) && isPowerOf2(m_Width))
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }

    void OpenGL_Texture::SetData(const Color* data, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        if (width == 0) width = m_Width;
        if (height == 0) height = m_Height;

        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    void OpenGL_Texture::Bind(uint32_t slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }
}
