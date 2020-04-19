#pragma once

#include "Reme/Renderer/Image.h"
#include "Reme/Renderer/Texture.h"

#include <glm/glm.hpp>

namespace Reme
{
    class BitmapTexture : public Texture
    {
    public:
        Ref<BitmapTexture> Create(uint32_t width, uint32_t height)
        {
            return CreateRef<BitmapTexture>(width, height);
        }

        Ref<BitmapTexture> Create(const Ref<Image>& image)
        {
            return CreateRef<BitmapTexture>(image);
        }

        Ref<BitmapTexture> Create(const std::string& path)
        {
            return CreateRef<BitmapTexture>(path);
        }

        BitmapTexture(uint32_t width, uint32_t height);
        BitmapTexture(const Ref<Image>& image);
        BitmapTexture(const std::string& path);
    public:
        ~BitmapTexture();
        
        inline uint32_t GetWidth() const override { return m_Image->GetWidth(); }
        inline uint32_t GetHeight() const override { return m_Image->GetHeight(); }
        void Resize(uint32_t width, uint32_t height);

        inline uint32_t GetInternalID() const override { return m_Texture->GetInternalID(); };

        inline Color GetPixel(uint32_t x, uint32_t y) const { return m_Image->GetPixel(x, y); }
        inline void SetPixel(uint32_t x, uint32_t y, const Color& color);
        
        inline const std::vector<Color>& GetPixelsData() const { return m_Image->GetPixelsData(); }
        inline void SetPixelsData(const Color* pixels);

        void GenerateMipmap() const override { m_Texture->GenerateMipmap(); }
        void SetData(const Color* data, uint32_t x = 0, uint32_t y = 0, uint32_t width = 0, uint32_t height = 0) override
        {
            ASSERT(false, "CAN NOT USE SetData() on BitmapTexture, use SetPixel() or SetPixelsData()");
        }

        void Bind(uint32_t slot = 0) override;
    private:
        bool m_Dirty = false;
        glm::uvec4 m_DirtyArea;
        Ref<Image> m_Image;
        Ref<Texture> m_Texture;
    };
}
