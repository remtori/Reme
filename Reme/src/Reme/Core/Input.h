#pragma once

#include "Reme/Events/Event.h"
#include "Reme/Events/KeyEvent.h"
#include "Reme/Events/MouseEvent.h"
#include "Reme/Core/KeyCodes.h"
#include "Reme/Core/MouseCodes.h"

#include <glm/glm.hpp>
#include <unordered_map>

namespace Reme
{
	class Input
	{
	public:
		enum class KeyState
		{
			KeyUp = 0, KeyDown = 1, KeyRepeat = 2
		};
	public:
		static void OnEvent(Event& event);
		static bool IsKeyPressed(KeyCode key);
		static bool IsKeyRepeated(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePos();
	private:
		static bool OnKeyDown(KeyDownEvent e);
		static bool OnKeyUp(KeyUpEvent e);
		static bool OnMouseDown(MouseDownEvent e);
		static bool OnMouseUp(MouseUpEvent e);
		static bool OnMouseMove(MouseMoveEvent e);

		struct InputData
		{
			std::unordered_map<uint16_t, KeyState> KeyMap;
			float mouseX, mouseY;
		};

		static InputData s_Data;
	};
}
