#include "RemePCH.h"
#include "Reme/Renderer/Image.h"
#include "Reme/Core/AssetManager.h"

#include <stb_image.h>

namespace Reme
{
    Image::Image(uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height), m_Pixels(width * height)
    {
    }

    Image::Image(const std::string& path)
    {
        int width, height, channels;
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        if (data == nullptr)
        {
            CORE_LOG_ERROR("Failed to load image \"{}\"", path);
            return;
        }

        m_Width = width;
        m_Height = height;
        m_Pixels.resize(width * height);
        memcpy(&m_Pixels[0], data, m_Pixels.size() * sizeof(Color));

        stbi_image_free(data);
    }

    Image::~Image()
    {
    }

    void Image::Copy(
        const Ref<Image>& source,
        uint32_t dX, uint32_t dY,
        uint32_t sX, uint32_t sY, uint32_t sW, uint32_t sH,
        bool applyAlpha
    )
    {
        PROFILE_FUNCTION();
        
        if (sW  > source->GetWidth()) sW = source->GetWidth();
        if (sH > source->GetHeight()) sH = source->GetHeight();

        int width  = sW;
        int height = sH;
        if (dX + width  > m_Width) width  = m_Width - dX;
        if (dY + height > m_Height) height = m_Height - dY;

        if (width <= 0 || height <= 0) return;

        int          pitch     = width;
        int          rows      = height;
        int          srcStride = source->GetWidth();
        int          dstStride = m_Width;
        const Color* srcPixels = &source->GetPixelsData()[sX + sY * source->GetWidth()];
        Color*       dstPixels = &m_Pixels[dX + dY * m_Width];

        // Copy the pixels
        if (applyAlpha)
        {
            // Interpolation using alpha values, pixel by pixel (slower)
            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < width; ++j)
                {
                    // Get a direct pointer to the components of the current pixel
                    const Color& src = *(srcPixels + j);
                    Color&       dst = *(dstPixels + j);

                    // Interpolate RGBA components using the alpha value of the source pixel
                    uint8_t alpha = src.a;
                    dst.r = (src.r * alpha + dst.r * (255 - alpha)) / 255;
                    dst.g = (src.g * alpha + dst.g * (255 - alpha)) / 255;
                    dst.b = (src.b * alpha + dst.b * (255 - alpha)) / 255;
                    dst.a = alpha + dst.a * (255 - alpha) / 255;
                }

                srcPixels += srcStride;
                dstPixels += dstStride;
            }
        }
        else
        {
            // Optimized copy ignoring alpha values, row by row (faster)
            for (int i = 0; i < rows; ++i)
            {
                std::memcpy(dstPixels, srcPixels, pitch * sizeof(Color));
                srcPixels += srcStride;
                dstPixels += dstStride;
            }
        }
    }
}
