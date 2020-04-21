#pragma once

#include "Reme/Core/Window.h"

namespace Reme
{
    class Test_Window : public Window
    {
    public:
        Test_Window(const WindowProps& props);
        ~Test_Window();

		virtual void PollEvent() override;
        virtual void SwapBuffers() override;
        virtual void MakeContextCurrent() override;

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
        virtual void SetSize(const uint32_t& width, const uint32_t& height) override;

        virtual void SetTitle(const std::string& title) override;
        virtual const std::string& GetTitle() const override;

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual void* GetNativeWindow() const override { return nullptr; };
		virtual void SetEventCallback(const EventCallbackFn& callback) override { Data.EventCallback = callback; };        

        enum class NativeFunc 
        {
            PollEvent,
            SwapBuffers,
            MakeContextCurrent,
        };

        struct WindowData
        {
            bool IsVSync;
            uint32_t Width, Height;
            std::string Title;
            EventCallbackFn EventCallback;
            std::vector<NativeFunc> Callstack;
        };

        WindowData Data;
    };
}
