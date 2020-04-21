#include "RemePCH.h"
#include "Reme/Core/Core.h"
#include "Reme/Core/Window.h"

#if defined(TEST)
#include "Impl/Windows/Test_Window.h"
#elif defined(_REME_USE_GLFW)
#include "Impl/Windows/GLFW_Window.h"
#endif

namespace Reme
{
    Ref<Window> Window::Create(const WindowProps& props)
    {
#if definded(TEST)
        return CreateRef<Test_Window>(props);
#elif defined(_REME_USE_GLFW)
        return CreateRef<GLFW_Window>(props);
#else
        CORE_ASSERT(false, "Can not create window for current platform");
        return nullptr;
#endif
    }
}
