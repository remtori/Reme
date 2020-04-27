#pragma once

#include "Reme/Renderer/RendererAPI.h"

namespace Reme
{
    class OpenGL_RendererAPI : public RendererAPI
    {
    public:
        void Init() override;
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        void SetClearColor(const Color& color) override;
        void Clear() override;
        void PollError() override;

        void DrawIndexed(DrawMode mode, uint32_t count, uint32_t offset) override;
        void DrawArrays(DrawMode mode, uint32_t count, uint32_t offset) override;

#ifdef TEST
        DrawCall GetDrawData() override { throw; }
#endif

        uint32_t GetMaxTextureUnit() override { return m_MaxTextureUnit; }
        uint32_t GetMaxTextureSize() override { return m_MaxTextureSize; }
    private:
        uint32_t m_MaxTextureUnit;
        uint32_t m_MaxTextureSize;
        bool m_UsePollError = true;
    };
}
