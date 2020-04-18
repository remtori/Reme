#include "RemePCH.h"
#include "Reme/Core/Core.h"
#include "Reme/Core/Window.h"

#ifdef _REME_USE_GLFW
#include "Impl/GLFW_Window.h"
#endif

namespace Reme
{
    Ref<Window> Window::Create(const WindowProps& props)
    {
#ifdef _REME_USE_GLFW
        return CreateRef<GLFW_Window>(props);
#else
        CORE_ASSERT(false, "Can not create window for current platform");
        return nullptr;
#endif
    }
}
