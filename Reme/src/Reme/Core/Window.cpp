#include "RemePCH.h"
#include "Reme/Core/Core.h"
#include "Reme/Core/Window.h"

#ifdef TEST
#include "Impl/Test/Test_Window.h"
#endif

#include "Impl/Windows/GLFW_Window.h"

namespace Reme
{
    Ref<Window> Window::Create(const WindowProps& props)
    {
#ifdef TEST
        return CreateRef<Test_Window>(props);
#endif

#if defined(REME_USE_GLFW)
        return CreateRef<GLFW_Window>(props);
#endif

        CORE_ASSERT(false, "Can not create window for current platform");
        return nullptr;
    }
}
