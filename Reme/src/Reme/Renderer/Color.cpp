#include "reme_pch.h"
#include "Reme/Renderer/Color.h"

namespace Reme
{
	const Color Color::Black(0, 0, 0);
	const Color Color::White(255, 255, 255);
	const Color Color::Red(255, 0, 0);
	const Color Color::Green(0, 255, 0);
	const Color Color::Blue(0, 0, 255);
	const Color Color::Yellow(255, 255, 0);
	const Color Color::Magenta(255, 0, 255);
	const Color Color::Cyan(0, 255, 255);
	const Color Color::Transparent(0, 0, 0, 0);

	Color::Color() :
		r(0), g(0), b(0), a(255)
	{
	}

	Color::Color(const Color& c) :
		r(c.r), g(c.g), b(c.b), a(c.a)
	{
	}

	Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
		r(red), g(green), b(blue), a(alpha)
	{
	}

	Color::Color(uint32_t color) : data(color)
	{
	}

	bool operator ==(const Color& left, const Color& right)
	{
		return left.data == right.data;
	}

	bool operator !=(const Color& left, const Color& right)
	{
		return !(left == right);
	}

	Color operator +(const Color& left, const Color& right)
	{
		return Color(uint8_t(std::min(int(left.r) + right.r, 255)),
			uint8_t(std::min(int(left.g) + right.g, 255)),
			uint8_t(std::min(int(left.b) + right.b, 255)),
			uint8_t(std::min(int(left.a) + right.a, 255)));
	}

	Color operator -(const Color& left, const Color& right)
	{
		return Color(uint8_t(std::max(int(left.r) - right.r, 0)),
			uint8_t(std::max(int(left.g) - right.g, 0)),
			uint8_t(std::max(int(left.b) - right.b, 0)),
			uint8_t(std::max(int(left.a) - right.a, 0)));
	}

	Color operator *(const Color& left, const Color& right)
	{
		return Color(uint8_t(int(left.r) * right.r / 255),
			uint8_t(int(left.g) * right.g / 255),
			uint8_t(int(left.b) * right.b / 255),
			uint8_t(int(left.a) * right.a / 255));
	}

	Color& operator +=(Color& left, const Color& right)
	{
		return left = left + right;
	}

	Color& operator -=(Color& left, const Color& right)
	{
		return left = left - right;
	}

	Color& operator *=(Color& left, const Color& right)
	{
		return left = left * right;
	}
}
