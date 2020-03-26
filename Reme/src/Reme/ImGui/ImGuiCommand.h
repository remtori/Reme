#pragma once

namespace Reme
{
    class ImGuiCommand
    {
    public:
        static void Init();
        static void Shutdown();

        static void Begin();
        static void End();
    };
}
