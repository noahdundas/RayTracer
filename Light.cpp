#include "Light.h"

Light::Light()
{
	orig = Point(0,0,0);
	col = Color(0,0,0);
}

Light::Light(Point p, Color c)
{
	orig = p;
	col = c;
}

Point Light::position() const
{
	return orig;
}

Color Light::color() const
{
	return col;
}

std::ostream& operator<<(std::ostream& os, const Light& l)
{
	os << "[Light: " << l.position() << ", " << l.color() << "]";
	return os;
}

std::istream& operator>>(std::istream& is, Light& l)
{
	char chToken;
	Point p;
	Color c;

	is >> p >> chToken;  // Read Point and comma
	is >> c;  			 // Read the Color

	l = Light(p, c);
	return is;
}
