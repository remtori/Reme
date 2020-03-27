#pragma once

#include "Reme/Core/KeyCodes.h"
#include "Reme/Core/MouseCodes.h"

namespace Reme
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePos();
	};
}
