#pragma once

#include <string>

namespace Reme
{
    class Texture
    {
    public:
        static Texture* Create(uint32_t width, uint32_t height);
        static Texture* Create(const std::string& path);
    public:

        virtual inline uint32_t GetWidth() const = 0;
        virtual inline uint32_t GetHeight() const = 0;
        virtual inline uint32_t GetInternalID() const = 0;

        virtual void SetData(void* data, uint32_t size) = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };
}
