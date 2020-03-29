#include "pch.h"

#include "Reme/Core/Application.h"
#include "Reme/ImGui/ImGuiCommand.h"
#include "Reme/Renderer/Renderer.h"

#include <chrono>

namespace Reme
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const WindowProps& props)
	{
		REME_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;

		m_Window = Window::Create(props);
		m_Window->SetEventCallback(REME_BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(true);

		m_Screen = CreateRef<Screen>();

		Renderer::Init();
		ImGuiCommand::Init();
	}

	Application::~Application()
	{
		ImGuiCommand::Shutdown();
		Renderer::Shutdown();
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(REME_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(REME_BIND_EVENT_FN(Application::OnWindowResize));

		if (!ImGuiCommand::ShouldSwallowEvent(event))
		{
			Input::OnEvent(event);
			m_Screen->OnEvent(event);
		}
	}

	void Application::Run()
	{
		typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimeStamp;

		TimeStamp currTime;
		TimeStamp lastTime = std::chrono::high_resolution_clock::now();
		float ellapsedTime;

		while (m_Running)
		{
			m_Window->PollEvent();

			currTime = std::chrono::high_resolution_clock::now();
			ellapsedTime = std::chrono::duration<float>(currTime - lastTime).count();
			while (ellapsedTime > DeltaTime)
			{
				m_Screen->OnUpdate(DeltaTime);
				ellapsedTime -= DeltaTime;
			}
			m_Screen->OnUpdate(ellapsedTime);
			lastTime = currTime;

			if (!m_Minimized)
			{
				m_Screen->OnRender();

				ImGuiCommand::Begin();
				m_Screen->OnImGuiRender();
				ImGuiCommand::End();
			}

			m_Window->SwapBuffers();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
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