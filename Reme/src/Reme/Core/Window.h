#pragma once

#include "reme_pch.h"
#include "Reme/Events/Event.h"

namespace Reme
{
    struct WindowProps
    {
        std::string Title;
        uint32_t Width, Height;
    };

    class Window
    {
    public:
        typedef std::function<void(Event&)> EventCallbackFn;

        virtual ~Window() = default;

		virtual void PollEvent() = 0;
        virtual void SwapBuffers() = 0;
        virtual void MakeContextCurrent() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
        virtual void SetSize(const uint32_t& width, const uint32_t& height) = 0;

        virtual void SetTitle(const std::string& title) = 0;
        virtual const std::string& GetTitle() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void* GetNativeWindow() const = 0;

		static Ref<Window> Create(const WindowProps& props);
    };
}
