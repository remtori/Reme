#pragma once

#include "Reme/Renderer/RendererAPI.h"

#include <glm/glm.hpp>

namespace Reme
{
    class Test_RendererAPI : public RendererAPI
    {
    public:
        void Init() override {}
        void Clear() override {}
        void PollError() override {}
        void SetClearColor(const Color& color) override { m_ClearColor = color; }

        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override 
        { 
            m_Viewport = { x, y, width, height }; 
        }

        void DrawIndexed(DrawMode mode, uint32_t count, uint32_t offset) override 
        { 
            m_LastDrawCall = { mode, count, offset, Test_VertexArray::BindedVAO }; 
        }

        void DrawArrays(DrawMode mode, uint32_t count, uint32_t offset) override 
        { 
            m_LastDrawCall = { mode, count, offset, Test_VertexArray::BindedVAO };
        }

        uint32_t GetMaxTextureUnit() override { return 2; }
        uint32_t GetMaxTextureSize() override { return 1024; }

        DrawCall GetDrawData() override { return m_LastDrawCall; }
    private:
        bool m_UsePollError = true;

        DrawCall m_LastDrawCall;
        glm::vec4 m_Viewport;
        Color m_ClearColor;
    };
}
