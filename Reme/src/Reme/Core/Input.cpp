#include "pch.h"
#include "Reme/Core/Input.h"
#include "Reme/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Reme
{
    bool Input::IsKeyPressed(KeyCode key)
	{
		int state = glfwGetKey((GLFWwindow*) Application::Get().GetWindow().GetNativeWindow(), (int) key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode btn)
	{
		int state = glfwGetMouseButton((GLFWwindow*) Application::Get().GetWindow().GetNativeWindow(), (int) btn);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> Input::GetMousePos()
	{
		double xpos, ypos;
		glfwGetCursorPos((GLFWwindow*) Application::Get().GetWindow().GetNativeWindow(), &xpos, &ypos);

		return { (float) xpos, (float) ypos };
	}
}
