#pragma once

#include "Reme/Graphics/Color.h"
#include "Reme/Graphics/Image.h"
#include "Reme/Core/AssetManager.h"

#include <string>

namespace Reme
{
    class Texture : public Asset
    {
    public:
        static Scope<Texture> Create(uint32_t width, uint32_t height);
        static Scope<Texture> Create(const Ref<Image>& image);
        static Scope<Texture> Create(const std::string& path);

        static Ref<Texture> Default;
        static Ref<Texture> White;
        static void Init();
    public:
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetInternalID() const = 0;

        virtual void GenerateMipmap() const = 0;
        virtual void SetData(const Color* data, uint32_t x = 0, uint32_t y = 0, uint32_t width = 0, uint32_t height = 0) = 0;

        virtual void Bind(uint32_t slot = 0) = 0;
    };
}
