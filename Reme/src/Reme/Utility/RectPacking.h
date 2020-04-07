#pragma once

#include <glm/glm.hpp>

namespace Reme
{    
	class RectPacking
	{
	public:
		// Unique identifier
		using UID = uint32_t;

		struct Input { UID uid; uint32_t w, h; };

		struct Rect { uint32_t x, y, w, h; };

		struct LayoutData
		{
			uint32_t Width, Height;
			std::vector<Rect> EmptySpaces;
			std::unordered_map<UID, Rect> Layout;
		};

		static void FindBestPack(const std::vector<Input>& rects, LayoutData& result);
	};
}
