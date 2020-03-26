#pragma once

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
        inline static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };
}
