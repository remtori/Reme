#pragma once

#include "Reme/Core/Core.h"
#include "Reme/Renderer/Image.h"
#include "Reme/Renderer/Texture.h"

#include <vector>

namespace Reme
{
    class Test_Texture : public Texture
    {
    public:
        static uint32_t BindedTexture;

        Test_Texture(uint32_t width, uint32_t height);
        Test_Texture(const Ref<Image>& image);
        ~Test_Texture();

        inline uint32_t GetWidth() const override { return m_Width;  }
        inline uint32_t GetHeight() const override { return m_Height; }
        inline uint32_t GetInternalID() const override { return 0; }
        void GenerateMipmap() const override {}

        void SetData(const Color* data, uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        const std::vector<Color>& GetData() const { return m_Data; }

        void Bind(uint32_t slot) override { BindedTexture = GetAssetID(); }
        bool IsBinded() { return BindedTexture == GetAssetID();  }
    private:
        uint32_t m_Width, m_Height;
        std::vector<Color> m_Data;
    };
}
