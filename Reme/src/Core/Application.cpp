#include "pch.h"

#include "Core/Application.h"
#include "Renderer/Renderer2D.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

namespace Reme
{
	Application::Application(const char* title, float screenWidth, float screenHeight)
	{
		m_WinInfo = WindowData{
			this, title,
			screenWidth, screenHeight
		};

		glfwSetErrorCallback([](int error, const char* description) {
			LOG_ERROR("{0}", description);
		});

		ASSERT(glfwInit(), "Failed to initialize GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			LOG_ERROR("Failed to create GLFW window!");
			exit(EXIT_FAILURE);
		}

		glfwSetWindowUserPointer(m_Window, &m_WinInfo);

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
				WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
				data->Width = width;
				data->Height = height;

				data->App->OnResize(width, height);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
						data->App->OnKeyboard(key, KeyState::DOWN);
						break;

					case GLFW_RELEASE:
						data->App->OnKeyboard(key, KeyState::UP);
						break;

					case GLFW_REPEAT:
						data->App->OnKeyboard(key, KeyState::REPEAT);
						break;
				}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->App->OnMouseMove(xpos, ypos);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
						data->App->OnMouseButton(button, KeyState::DOWN);
						break;
					case GLFW_RELEASE:
						data->App->OnMouseButton(button, KeyState::UP);
				}
		});

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			LOG_ERROR("Failed to initialize GLAD");
			exit(EXIT_FAILURE);
		}

		LOG_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
		LOG_INFO("GLSL Version: {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));
		LOG_INFO("Renderer: {0}", glGetString(GL_RENDERER));

		glfwSwapInterval(1);

		// ImGui Init
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui::StyleColorsDark();
		ImGui::GetStyle().WindowRounding = 0.0f;

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		Renderer2D::Init();
	}

	Application::~Application()
	{
		// ImGui Shutdown
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		Renderer2D::Shutdown();

		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Application::Run()
	{
		double currTime;
		double lastTime = 0;
		double elapsedTime;
		glfwSetTime(lastTime);
		glfwMaximizeWindow(m_Window);

		while (!glfwWindowShouldClose(m_Window))
		{
			glfwPollEvents();

			currTime = glfwGetTime();
			elapsedTime = currTime - lastTime;
			while (elapsedTime > deltaTime)
			{
				OnUpdate(deltaTime);
				elapsedTime -= deltaTime;
			}
			OnUpdate(elapsedTime);
			lastTime = currTime;

			OnRender();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			OnImGuiRender();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(m_Window);
		}
	}

	void Application::OnResize(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	bool Application::IsKeyPressed(int key)
	{
		int state = glfwGetKey(m_Window, key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Application::IsMouseButtonPressed(int btn)
	{
		int state = glfwGetMouseButton(m_Window, btn);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> Application::GetMousePos()
	{
		double xpos, ypos;
		glfwGetCursorPos(m_Window, &xpos, &ypos);

		return { (float) xpos, (float) ypos };
	}

	glm::vec2 Application::ConvertCoord(const glm::vec2& pos)
	{
		return {
			(2.0 * pos.x + 1.0) / m_WinInfo.Width - 1.0,
			(2.0 * pos.y + 1.0) / m_WinInfo.Height - 1.0
		};
	}

	// Renderer2D Utility Method
	void Application::DrawRect(glm::vec4 color, glm::vec2 position, glm::vec2 scale)
	{
		glm::vec2 p = ConvertCoord(position);
		glm::vec2 s = ConvertCoord(scale);

		// Renderer2D Draw implementation will convert
		// (Texture*) 1 to a white texture
		Renderer2D::Draw(
			(Texture*) 1,
			{ 0.0f, 0.0f }, { 0.0f, 0.0f },
			{ p.x, p.y, zIndex }, s,
			color
		);
	}

	void Application::DrawTexture(Texture* texture, glm::vec2 destPos, glm::vec2 destScale)
	{
		glm::vec2 p = ConvertCoord(destPos);
		glm::vec2 s =
			(destScale.x == 0.0f && destScale.y == 0.0f)
			? glm::vec2{ texture->GetWidth(), texture->GetHeight() }
			: ConvertCoord(destScale);

		NoScaleDrawTexture(texture, { 0.0f, 0.0f }, { 1.0f, 1.0f }, p, s);
	}

	void Application::DrawTexture(Texture* texture, glm::vec2 srcPos, glm::vec2 srcScale, glm::vec2 destPos, glm::vec2 destScale)
	{
		NoScaleDrawTexture(texture, ConvertCoord(srcPos), ConvertCoord(srcScale), ConvertCoord(destPos), ConvertCoord(destScale));
	}

	void Application::NoScaleDrawTexture(Texture* texture, glm::vec2 srcPos, glm::vec2 srcScale, glm::vec2 destPos, glm::vec2 destScale)
	{
		Renderer2D::Draw(texture, srcPos, srcScale, { destPos.x, destPos.y, zIndex }, destScale);
	}
}