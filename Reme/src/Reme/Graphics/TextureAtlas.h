#pragma once

#include "Reme/Graphics/Image.h"
#include "Reme/Graphics/Texture.h"

#include <glm/glm.hpp>

namespace Reme
{
    class TextureAtlas
    {
    public:
        static Scope<TextureAtlas> Create()
        {
            return CreateScope<TextureAtlas>();
        }
    public:
        TextureAtlas();
        ~TextureAtlas();        

        void AddImage(const Ref<Image>& image);
        bool HasImage(const Ref<Image>& image);

        void Bind();
        glm::vec2 GetUV(const Ref<Image>& image, uint32_t x, uint32_t y);

        void PackImages();
    private:
        struct Rect { uint32_t x, y, w, h; };
        struct LayoutData 
        {
            uint32_t Width, Height;
            std::vector<Rect> EmptySpaces;
            std::unordered_map<uint32_t, Rect> AtlasLayout;
        };        
        bool TryPackImages(LayoutData* data, uint32_t width, uint32_t height);
        bool PutImage(const Ref<Image>& image, LayoutData* data);
    private:
        LayoutData m_Data;
        std::vector<Ref<Image>> m_PendingImage;
        Ref<Texture> m_Texture;
        Ref<Image> m_Image;
        bool m_Dirty;
    };
}
