#include "RemePCH.h"
#include "Reme/Core/Input.h"

namespace Reme
{
	Input::InputData Input::s_Data;

	void Input::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyDownEvent>(Input::OnKeyDown);
		dispatcher.Dispatch<KeyUpEvent>(Input::OnKeyUp);
		dispatcher.Dispatch<MouseDownEvent>(Input::OnMouseDown);
		dispatcher.Dispatch<MouseUpEvent>(Input::OnMouseUp);
		dispatcher.Dispatch<MouseMoveEvent>(Input::OnMouseMove);
	}

    bool Input::IsKeyPressed(KeyCode key)
	{
		if (s_Data.KeyMap.count((uint16_t) key))
		{
			auto state = s_Data.KeyMap[(uint16_t) key];
			return state == KeyState::KeyDown || state == KeyState::KeyRepeat;
		}

		return false;
	}

	bool Input::IsKeyRepeated(KeyCode key)
	{
		if (s_Data.KeyMap.count((uint16_t) key))
		{
			return s_Data.KeyMap[(uint16_t) key] == KeyState::KeyRepeat;
		}

		return false;
	}

	bool Input::IsMouseButtonPressed(MouseCode btn)
	{
		if (s_Data.KeyMap.count((uint16_t) btn))
		{
			auto state = s_Data.KeyMap[(uint16_t) btn];
			return state == KeyState::KeyDown;
		}

		return false;
	}

	glm::vec2 Input::GetMousePos()
	{
		return { s_Data.mouseX, s_Data.mouseY };
	}

	bool Input::OnKeyDown(KeyDownEvent e)
	{
		s_Data.KeyMap[(uint16_t) e.GetKeyCode()] = e.GetRepeatCount() ? KeyState::KeyRepeat : KeyState::KeyDown;
		return false;
	}

	bool Input::OnKeyUp(KeyUpEvent e)
	{
		s_Data.KeyMap[(uint16_t) e.GetKeyCode()] = KeyState::KeyUp;
		return false;
	}

	bool Input::OnMouseDown(MouseDownEvent e)
	{
		s_Data.KeyMap[(uint16_t) e.GetMouseButton()] = KeyState::KeyDown;
		return false;
	}

	bool Input::OnMouseUp(MouseUpEvent e)
	{
		s_Data.KeyMap[(uint16_t) e.GetMouseButton()] = KeyState::KeyUp;
		return false;
	}

	bool Input::OnMouseMove(MouseMoveEvent e)
	{
		s_Data.mouseX = e.GetX();
		s_Data.mouseY = e.GetY();
		return false;
	}
}
