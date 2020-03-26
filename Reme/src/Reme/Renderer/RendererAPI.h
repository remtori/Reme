#pragma once

#include "Reme/Renderer/Color.h"
#include "Reme/Renderer/VertexArray.h"

namespace Reme
{
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

        virtual void DrawIndexed(uint32_t count, uint32_t offset) = 0;
        virtual void DrawArrays(uint32_t count, uint32_t offset) = 0;

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

        inline static void DrawIndexed(uint32_t count, uint32_t offset = 0)
        {
            s_RendererAPI->DrawIndexed(count, offset);
        }

        inline static void DrawArrays(uint32_t count, uint32_t offset = 0)
        {
            s_RendererAPI->DrawArrays(count, offset);
        }
    private:
        static RendererAPI* s_RendererAPI;
    };
}
