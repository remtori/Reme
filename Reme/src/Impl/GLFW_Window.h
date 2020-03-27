#pragma once

#include "Reme/Core/Window.h"

typedef struct GLFWwindow GLFWwindow;

namespace Reme
{
    class GLFW_Window : public Window
    {
    public:
        GLFW_Window(const WindowProps& props);
        ~GLFW_Window();

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

		virtual void* GetNativeWindow() const override { return m_Window; };
		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            bool IsVSync;
            uint32_t Width, Height;
            std::string Title;
            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}
