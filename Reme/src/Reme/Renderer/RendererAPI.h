#pragma once

#include "Reme/Renderer/Color.h"
#include "Reme/Renderer/VertexArray.h"

namespace Reme
{
    enum class DrawMode
    {
        POINTS, LINE_STRIP, LINE_LOOP, LINES, TRIANGLE_STRIP, TRIANGLE_FAN, TRIANGLES
    };

    class RendererAPI
    {
    public:
        enum API
        {
            None = 0, OpenGL
        };
    public:
        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const Color& color) = 0;
        virtual void Clear() = 0;
        virtual void PollError() = 0;

        virtual void DrawIndexed(DrawMode mode, uint32_t count, uint32_t offset) = 0;
        virtual void DrawArrays(DrawMode mode, uint32_t count, uint32_t offset) = 0;

        inline static API GetAPI() { return s_API; }
        static RendererAPI* Create();
    private:
        static API s_API;
    };

    class RenderCommand
    {
    public:
        inline static void Init()
        {
            s_RendererAPI->Init();
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_RendererAPI->SetViewport(x, y, width, height);
        }

        inline static void SetClearColor(const Color& color)
        {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear()
        {
            s_RendererAPI->Clear();
        }

        inline static void PollError()
        {
            s_RendererAPI->PollError();
        }

        inline static void DrawIndexed(DrawMode mode, uint32_t count, uint32_t offset = 0)
        {
            s_RendererAPI->DrawIndexed(mode, count, offset);
        }

        inline static void DrawArrays(DrawMode mode, uint32_t count, uint32_t offset = 0)
        {
            s_RendererAPI->DrawArrays(mode, count, offset);
        }
    private:
        static RendererAPI* s_RendererAPI;
    };
}
