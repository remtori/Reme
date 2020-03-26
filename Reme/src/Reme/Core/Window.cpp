#include "pch.h"
#include "Reme/Core/Core.h"
#include "Reme/Core/Window.h"

#ifdef _REME_USE_GLFW
#include "Impl/GLFW_Window.h"
#endif

namespace Reme
{
    Window* Window::Create(const WindowProps& props)
    {
#ifdef _REME_USE_GLFW
        return new GLFW_Window(props);
#else
        REME_ASSERT(false, "Can not create window for current platform");
        return nullptr;
#endif
    }
}
