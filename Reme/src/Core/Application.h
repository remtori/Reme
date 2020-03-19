#pragma once

#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"
#include "Renderer/Color.h"
#include "Renderer/Texture.h"

#include <glm/glm.hpp>

typedef struct GLFWwindow GLFWwindow;

namespace Reme
{
	class Application {
	protected:
		double deltaTime = 1000.0 / 60;
	public:
		Application(const char* title = "Reme Engine", float screenWidth = 640, float screenHeight = 480);
		virtual ~Application();

		void Run();
	protected:
		/**
		 * OnRender function only being called when we draw a new frame
		 */
		virtual void OnRender() = 0;

		/**
		 * OnUpdate is guarantee to run every "deltaTime", which default to 1/60 of a second
		 */
		virtual void OnUpdate(double ellapsedTime) {};
		virtual void OnImGuiRender() {};

		virtual void OnResize(int width, int height) {};
		virtual void OnKeyboard(KeyCode keyCode, KeyState keyState) {};
		virtual void OnMouseMove(float x, float y) {};
		virtual void OnMouseButton(MouseCode btn, KeyState keyState) {};

		bool IsKeyPressed(KeyCode key);
		bool IsMouseButtonPressed(MouseCode button);
		std::pair<float, float> GetMousePos();
	protected:
		GLFWwindow* m_Window;

		struct WindowData
		{
			Application* App;
			const char* Title;
			float Width, Height;
		};
		WindowData m_WinInfo;
	// Renderer2D Utility Method
	protected:
		void DrawRect(Color color, glm::vec2 position, glm::vec2 scale);
		void DrawTexture(Texture* texture, glm::vec2 destPos, glm::vec2 destScale = { 0.0f, 0.0f });
		void DrawTexture(Texture* texture, glm::vec2 srcPos, glm::vec2 srcScale, glm::vec2 destPos, glm::vec2 destScale);
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
