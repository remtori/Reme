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
            None = 0, OpenGL, Test
        };
    public:
        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const Color& color) = 0;
        virtual void Clear() = 0;
        virtual void PollError() = 0;

        virtual void DrawIndexed(DrawMode mode, uint32_t count, uint32_t offset) = 0;
        virtual void DrawArrays(DrawMode mode, uint32_t count, uint32_t offset) = 0;

        virtual uint32_t GetMaxTextureUnit() = 0;
        virtual uint32_t GetMaxTextureSize() = 0;

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
            PROFILE_FUNCTION();
            s_RendererAPI->Init();
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            PROFILE_FUNCTION();
            s_RendererAPI->SetViewport(x, y, width, height);
        }

        inline static void SetClearColor(const Color& color)
        {
            PROFILE_FUNCTION();
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear()
        {
            PROFILE_FUNCTION();
            s_RendererAPI->Clear();
        }

        inline static void PollError()
        {
            PROFILE_FUNCTION();
            s_RendererAPI->PollError();
        }

        inline static void DrawIndexed(DrawMode mode, uint32_t count, uint32_t offset = 0)
        {
            PROFILE_FUNCTION();
            s_RendererAPI->DrawIndexed(mode, count, offset);
        }

        inline static void DrawArrays(DrawMode mode, uint32_t count, uint32_t offset = 0)
        {
            PROFILE_FUNCTION();
            s_RendererAPI->DrawArrays(mode, count, offset);
        }

        inline static uint32_t GetMaxTextureUnit()
        {
            PROFILE_FUNCTION();
            return s_RendererAPI->GetMaxTextureUnit();
        }

        inline static uint32_t GetMaxTextureSize()
        {
            PROFILE_FUNCTION();
            return s_RendererAPI->GetMaxTextureSize();
        }

    private:
        static RendererAPI* s_RendererAPI;
    };
}
