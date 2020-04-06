#pragma once

#include "Reme/Graphics/Texture.h"

namespace Reme
{
    class TextureAtlas
    {
    public:
        Ref<TextureAtlas> Create();
    public:
        TextureAtlas();
        ~TextureAtlas();

        void Add(Ref<Texture> texture);
    private:
        Scope<Texture> m_Texture;
    };
}
