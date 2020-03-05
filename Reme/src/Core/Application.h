#pragma once

#include <glm/glm.hpp>
#include "Renderer/Texture.h"

typedef struct GLFWwindow GLFWwindow;

namespace Reme
{
	enum KeyState {
		UP, DOWN, REPEAT
	};

	class Application {
	public:
		Application(const char* title = "Reme Engine", float screenWidth = 640, float screenHeight = 360);
		virtual ~Application();

		void Run();
	protected:
		virtual void OnRender() = 0;
		virtual void OnUpdate(double deltaTime) {};
		virtual void OnImGuiRender() {};

		virtual void OnResize(int width, int height);

		virtual void OnKeyboard(int keyCode, int keyState) {};

		virtual void OnMouseMove(float x, float y) {};
		virtual void OnMouseButton(int btn, int keyState) {};

		bool IsKeyPressed(int key);
		bool IsMouseButtonPressed(int button);
		std::pair<float, float> GetMousePos();

		glm::vec2 ConvertCoord(const glm::vec2& pos);
	protected:
		double deltaTime = 1000.0 / 60;
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
		float zIndex = 0.0f;
		void DrawRect(glm::vec4 color, glm::vec2 position, glm::vec2 scale);
		void DrawTexture(Texture* texture, glm::vec2 destPos, glm::vec2 destScale = { 0.0f, 0.0f });
		void DrawTexture(Texture* texture, glm::vec2 srcPos, glm::vec2 srcScale, glm::vec2 destPos, glm::vec2 destScale);
	private:
		void NoScaleDrawTexture(Texture* texture, glm::vec2 srcPos, glm::vec2 srcScale, glm::vec2 destPos, glm::vec2 destScale);
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
