#include "reme_pch.h"
#include "Reme/Renderer/TextureAtlas.h"
#include "Reme/Renderer/RendererAPI.h"

namespace Reme
{
    TextureAtlas::TextureAtlas()
        : m_Dirty(false)
    {
    }

    TextureAtlas::~TextureAtlas()
    {
    }

    void TextureAtlas::AddImage(const Ref<Image>& image)
    {
        m_PendingImage.push_back(image);
        m_Dirty = true;
    }

    bool TextureAtlas::HasImage(const Ref<Image>& image)
    {
        REME_ASSERT(!m_Dirty, "TextureAtlas is dirty, you need to call TextureAtlas::LayoutImages() before use this method!");
        return m_Data.AtlasLayout.find(image->GetAssetID()) != m_Data.AtlasLayout.end();
    }

    void TextureAtlas::Bind()
    {
        REME_ASSERT(!m_Dirty, "TextureAtlas is dirty, you need to call TextureAtlas::LayoutImages() before use this method!");
        m_Texture->Bind();
    }

    glm::vec2 TextureAtlas::GetUV(const Ref<Image>& image, uint32_t x, uint32_t y)
    {
        REME_ASSERT(!m_Dirty, "TextureAtlas is dirty, you need to call TextureAtlas::LayoutImages() before use this method!");
        auto o = m_Data.AtlasLayout.at(image->GetAssetID());

        x %= image->GetWidth();
        y %= image->GetHeight();
        return {
            (float) (x + o.x) / (float) m_Texture->GetWidth(),
            (float) (y + o.y) / (float) m_Texture->GetHeight(),
        };
    }

    void TextureAtlas::PackImages()
    {
        static const uint32_t MAX_ATLAS_DIFF = 64;
        static const uint32_t MAX_TEXTURE_SIZE = RenderCommand::GetMaxTextureSize();

        // Restore the packed image to pending image and repack everything

        // Sort the images by: area, perimeter, bigger side, width, height, a pathological multiplier
        // Pathological multiplier: max(w, h) / min(w, h) * w * h

        LayoutData bestLayout;
        REME_ASSERT(
            TryPackImages(&bestLayout, MAX_TEXTURE_SIZE, MAX_TEXTURE_SIZE),
            "Can not pack all the image to one Texture Atlas, consider using 2 or more Atlas"
        );

        // Binary searching for the best Atlas size
        auto findBestPack = [&](uint8_t xMul, uint8_t yMul)
        {
            uint32_t width = bestLayout.Width;
            uint32_t height = bestLayout.Height;
            uint32_t step = xMul ? width / 2 : height / 2;
            uint32_t startingArea = width * height;

            LayoutData betterLayout;

            width -= (width / 2) * xMul;
            height -= (height / 2) * yMul;

            while (true)
            {
                if (TryPackImages(&betterLayout, width, height))
                {
                    // Insert everything successfully
                    if (step < MAX_ATLAS_DIFF) return betterLayout;

                    width -= step * xMul;
                    height -= step * yMul;
                }
                else
                {
                    // Failed to insert something
                    width += step * xMul;
                    height += step * yMul;
                    if (width * height > startingArea) throw 0;
                }
            }
        };

        auto trial = [&](uint8_t xMul, uint8_t yMul)
        {
            try {
                bestLayout = findBestPack(xMul, yMul);
            }
            catch(int _) {}
        };

        trial(1, 1);
        trial(1, 0);
        trial(0, 1);

        m_Image = Image::Create(bestLayout.Width, bestLayout.Height);
        for (auto img : m_PendingImage)
        {
            const Rect& r = bestLayout.AtlasLayout.at(img->GetAssetID());
            m_Image->Copy(img, r.x, r.y);
        }

        m_Texture = Texture::Create(m_Image);
        m_Data = bestLayout;
        m_PendingImage.clear();
        m_Dirty = false;
    }

    bool TextureAtlas::TryPackImages(LayoutData* data, uint32_t width, uint32_t height)
    {
        data->Width = width;
        data->Height = height;
        // Just In Case
        data->EmptySpaces.clear();
        data->AtlasLayout.clear();

        data->EmptySpaces.push_back({ 0, 0, width, height });

        for (const auto& img : m_PendingImage)
        {
            if (!PutImage(img, data)) return false;
        }

        return true;
    }

    bool TextureAtlas::PutImage(const Ref<Image>& img, LayoutData* data)
    {
        uint32_t width = img->GetWidth();
        uint32_t height = img->GetHeight();

        int32_t candidate_space_index = -1;
        for (int32_t i = data->EmptySpaces.size() - 1; i >= 0; --i)
        {
            const Rect& r = data->EmptySpaces.at(i);
            if (r.w >= width && r.h >= height)
            {
                candidate_space_index = i;
                break;
            }
        }

        if (candidate_space_index == -1) return false;

        const Rect& emptySpace = data->EmptySpaces.at(candidate_space_index);
        const auto free_w = emptySpace.w - width;
		const auto free_h = emptySpace.h - height;

        data->AtlasLayout[img->GetAssetID()] = {
            emptySpace.x,
            emptySpace.y,
            width,
            height,
        };

        if (free_w == 0 && free_h == 0)
        {
            return true;
        }

        if (free_w == 0)
        {
            data->EmptySpaces.push_back({
                emptySpace.x,
                emptySpace.y + height,
                emptySpace.w,
                free_h,
            });
            return true;
        }

        if (free_h == 0)
        {
            data->EmptySpaces.push_back({
                emptySpace.x + width,
                emptySpace.y,
                free_w,
                emptySpace.h,
            });

            return true;
        }

        if (free_w > free_h)
        {
            data->EmptySpaces.push_back({
                emptySpace.x + width,
                emptySpace.y,
                free_w,
                emptySpace.h,
            });

            data->EmptySpaces.push_back({
                emptySpace.x,
                emptySpace.y + height,
                width,
                free_h,
            });

            return true;
        }

        data->EmptySpaces.push_back({
            emptySpace.x,
            emptySpace.y + height,
            emptySpace.w,
            free_h,
        });

        data->EmptySpaces.push_back({
            emptySpace.x + width,
            emptySpace.y,
            free_w,
            height,
        });

        return true;
    }
}
