#pragma once

#include "Reme/Renderer/RendererAPI.h"

#include <glm/glm.hpp>

namespace Reme
{
    class Test_RendererAPI : public RendererAPI
    {
    public:
        void Init() override {}
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override { m_Viewport = { x, y, width, height }; }
        void SetClearColor(const Color& color) override { m_ClearColor = color; }
        void Clear() override {}
        void PollError() override {}

        void DrawIndexed(DrawMode mode, uint32_t count, uint32_t offset) override { m_LastDrawCall = { mode, count, offset }; }
        void DrawArrays(DrawMode mode, uint32_t count, uint32_t offset) override { m_LastDrawCall = { mode, count, offset }; }

        uint32_t GetMaxTextureUnit() override { return m_MaxTextureUnit; }
        uint32_t GetMaxTextureSize() override { return m_MaxTextureSize; }

        struct DrawCall
        {
            DrawMode mode;
            uint32_t count;
            uint32_t offset;
        };

        DrawCall GetDrawData() { return m_LastDrawCall; }
    private:
        uint32_t m_MaxTextureUnit;
        uint32_t m_MaxTextureSize;
        bool m_UsePollError = true;

        DrawCall m_LastDrawCall;
        glm::vec4 m_Viewport;
        Color m_ClearColor;
    };
}
