#pragma once

namespace Reme
{
	class Color
	{
	public:
		Color();
		Color(const Color& c);
		Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
		explicit Color(uint32_t hexColor);

		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;
		static const Color Transparent;

		union {
			struct { uint8_t r, g, b, a; };
			uint32_t data;
		};
	};

	bool operator ==(const Color& left, const Color& right);
	bool operator !=(const Color& left, const Color& right);
	Color operator +(const Color& left, const Color& right);
	Color operator -(const Color& left, const Color& right);
	Color operator *(const Color& left, const Color& right);
	Color& operator +=(Color& left, const Color& right);
	Color& operator -=(Color& left, const Color& right);
	Color& operator *=(Color& left, const Color& right);
}
