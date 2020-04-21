#include "RemePCH.h"
#include "Impl/Test/Test_Window.h"

namespace Reme
{
    Test_Window::Test_Window(const WindowProps& props)
    {
        Data.Title = props.Title;
		Data.Width = props.Width;
		Data.Height = props.Height;

        // Note: We do not implement event callback here
        // We can test-fire event by using Data.EventCallbackFN(Event)
    }

    Test_Window::~Test_Window()
    {
    }

    void Test_Window::PollEvent()
    {
        Data.Callstack.push_back(NativeFunc::PollEvent);
    }

    void Test_Window::SwapBuffers()
    {
        Data.Callstack.push_back(NativeFunc::SwapBuffers);
    }

    void Test_Window::MakeContextCurrent()
    {
        Data.Callstack.push_back(NativeFunc::MakeContextCurrent);
    }

    uint32_t Test_Window::GetWidth() const
    {
        return Data.Width;
    }

    uint32_t Test_Window::GetHeight() const
    {
        return Data.Height;
    }

    void Test_Window::SetSize(const uint32_t& width, const uint32_t& height)
    {
        Data.Width = width;
        Data.Height = height;
    }

    const std::string& Test_Window::GetTitle() const
    {
        return Data.Title;
    }

    void Test_Window::SetTitle(const std::string& title)
    {
        Data.Title = title;
    }

    void Test_Window::SetVSync(bool enabled)
    {
        Data.IsVSync = enabled;
    }

    bool Test_Window::IsVSync() const
    {
        return Data.IsVSync;
    }
}
