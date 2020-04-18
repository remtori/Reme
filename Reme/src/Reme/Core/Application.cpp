#include "reme_pch.h"

#include "Reme/Core/Application.h"
#include "Reme/ImGui/ImGuiCommand.h"
#include "Reme/Renderer/Renderer.h"

#include <chrono>

namespace Reme
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const WindowProps& props)
	{
		PROFILE_FUNCTION();

		CORE_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;

		m_Window = Window::Create(props);
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(true);

		m_Screen = CreateRef<Screen>();

		Renderer::Init();
		ImGuiCommand::Init();
	}

	Application::~Application()
	{
		PROFILE_FUNCTION();

		ImGuiCommand::Shutdown();
		Renderer::Shutdown();
	}

	void Application::OnEvent(Event& event)
	{
		PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		if (!ImGuiCommand::ShouldSwallowEvent(event))
		{
			Input::OnEvent(event);
			m_Screen->OnEvent(event);
		}
	}

	void Application::Run()
	{
		PROFILE_FUNCTION();
		typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimeStamp;

		TimeStamp currTime;
		TimeStamp lastTime = std::chrono::high_resolution_clock::now();
		float elapsedTime;

		while (m_Running)
		{
			PROFILE_SCOPE("RunLoop");
			
			{
				PROFILE_SCOPE("WindowPollEvent");
				m_Window->PollEvent();
			}

			{
				PROFILE_SCOPE("AppUpdate");

				currTime = std::chrono::high_resolution_clock::now();
				elapsedTime = std::chrono::duration<float>(currTime - lastTime).count();
				while (elapsedTime >= DeltaTime)
				{
					m_Screen->OnUpdate(DeltaTime);
					elapsedTime -= DeltaTime;
				}
				lastTime = currTime;
			}

			if (!m_Minimized)
			{
				m_Screen->OnRender();
				
				ImGuiCommand::Begin();
				m_Screen->OnImGuiRender();
				ImGuiCommand::End();
			}

			{
				PROFILE_SCOPE("WindowSwapBuffer");
				m_Window->SwapBuffers();
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}