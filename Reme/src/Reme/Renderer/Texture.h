#pragma once

#include <string>

namespace Reme
{
    class Texture
    {
    public:
        static Ref<Texture> Create(uint32_t width, uint32_t height);
        static Ref<Texture> Create(const std::string& path);

        static Ref<Texture> Default;
        static Ref<Texture> White;
        static void Init();
    public:

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetInternalID() const = 0;

        virtual void SetData(void* data, uint32_t size) = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };
}
