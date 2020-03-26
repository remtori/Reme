#pragma once

#include "Reme/Events/ApplicationEvent.h"

namespace Reme
{
    class Renderer
    {
    public:
        static void Init();
        static void Shutdown();

        static void OnWindowResize(float width, float height);
    };
}
