#include "reme_pch.h"
#include "Impl/GLFW_Window.h"
#include "Reme/Events/ApplicationEvent.h"
#include "Reme/Events/KeyEvent.h"
#include "Reme/Events/MouseEvent.h"

#include <GLFW/glfw3.h>

namespace Reme
{
    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description)
	{
		CORE_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
	}

    GLFW_Window::GLFW_Window(const WindowProps& props)
    {
        m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

        CORE_LOG_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (s_GLFWWindowCount == 0)
		{
			int success = glfwInit();
			REME_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

        m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
        s_GLFWWindowCount++;

		if (!m_Window)
		{
			glfwTerminate();
			CORE_LOG_ERROR("Failed to create GLFW window!");
			exit(EXIT_FAILURE);
		}

		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
				WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
				data->Width = width;
				data->Height = height;

                WindowResizeEvent e(width, height);
                data->EventCallback(e);
		});

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data->EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
				WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyDownEvent event(static_cast<KeyCode>(key), 0);
						data->EventCallback(event);
						break;
					}

					case GLFW_RELEASE:
					{
						KeyUpEvent event(static_cast<KeyCode>(key));
						data->EventCallback(event);
						break;
					}

					case GLFW_REPEAT:
					{
						KeyDownEvent event(static_cast<KeyCode>(key), 1);
						data->EventCallback(event);
						break;
					}
				}
		});

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
			KeyPressEvent event(static_cast<KeyCode>(keycode));
			data->EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
            MouseMoveEvent event((float) xpos, (float) ypos);
			data->EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
				WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseDownEvent event(static_cast<MouseCode>(button));
						data->EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseUpEvent event(static_cast<MouseCode>(button));
						data->EventCallback(event);
						break;
					}
				}
		});

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);

			MouseScrollEvent event((float) xOffset, (float) yOffset);
			data->EventCallback(event);
		});

		MakeContextCurrent();
    }

    GLFW_Window::~GLFW_Window()
    {
        glfwDestroyWindow(m_Window);
        s_GLFWWindowCount--;

        if (s_GLFWWindowCount == 0)
        {
            glfwTerminate();
        }
    }

    void GLFW_Window::PollEvent()
    {
        glfwPollEvents();
    }

    void GLFW_Window::SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }

    void GLFW_Window::MakeContextCurrent()
    {
        glfwMakeContextCurrent(m_Window);
    }

    uint32_t GLFW_Window::GetWidth() const
    {
        return m_Data.Width;
    }

    uint32_t GLFW_Window::GetHeight() const
    {
        return m_Data.Height;
    }

    void GLFW_Window::SetSize(const uint32_t& width, const uint32_t& height)
    {
        m_Data.Width = width;
        m_Data.Height = height;
        glfwSetWindowSize(m_Window, width, height);
    }


    const std::string& GLFW_Window::GetTitle() const
    {
        return m_Data.Title;
    }

    void GLFW_Window::SetTitle(const std::string& title)
    {
        m_Data.Title = title;
        glfwSetWindowTitle(m_Window, title.c_str());
    }


    void GLFW_Window::SetVSync(bool enabled)
    {
        m_Data.IsVSync = enabled;

        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
    }

    bool GLFW_Window::IsVSync() const
    {
        return m_Data.IsVSync;
    }
}
