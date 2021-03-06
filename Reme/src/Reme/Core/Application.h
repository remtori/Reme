#pragma once

#include "Reme/Core/Input.h"
#include "Reme/Core/Window.h"
#include "Reme/Events/ApplicationEvent.h"
#include "Reme/Core/Screen.h"

int main(int argc, char** argv);

namespace Reme
{
	class Application {
	public:
		// Maximum elapsed time allow between update (in seconds)
		float DeltaTime = 1.0 / 60;
	public:
		Application(const WindowProps& props = { "Reme Engine", 1280, 720 });
		~Application();

		inline Screen& GetScreen() { return *m_Screen; }
		void SetScreen(const Ref<Screen>& screen) { m_Screen = screen; }

		void OnEvent(Event& event);

		inline Window& GetWindow() { return *m_Window; }
		static inline Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Ref<Window> m_Window;
		Ref<Screen> m_Screen;
		bool m_Running = true;
		bool m_Minimized = false;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
