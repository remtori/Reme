#pragma once

#include "Reme/Events/Event.h"

namespace Reme
{
    class ImGuiCommand
    {
    public:
        static void Init();
        static void Shutdown();

        static void Begin();
        static void End();

        static bool ShouldSwallowEvent(Event& event);
    };
}
