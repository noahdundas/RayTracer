#include "Color.h"

#include <assert.h>
#include <ostream>
#include <istream>
#include <string>
using namespace std;


Color::Color()
	: Color(0.0, 0.0, 0.0)
{}


Color::Color(float r, float g, float b) 
	: r_(r), g_(g), b_(b)
{
	assert(r_ >= 0.0);
	assert(g_ >= 0.0);
	assert(b_ >= 0.0);

	r_ = (r_ > 1.0) ? 1.0 : r_;
	g_ = (g_ > 1.0) ? 1.0 : g_;
	b_ = (b_ > 1.0) ? 1.0 : b_;
}


float Color::r() const { return r_; }
float Color::g() const { return g_; }
float Color::b() const { return b_; }

float Color::gray()
{
	float r = 0.299*r_;
	float g = 0.587*g_;
	float b = 0.114*b_;
	float result = r+g+b;
	return result;
}

Color operator+(const Color& color1, const Color& color2)
{ 
	return Color( color1.r() + color2.r(),
		      color1.g() + color2.g(),
		      color1.b() + color2.b() );
}


Color operator*(const Color& color1, const Color& color2)
{
	return Color( color1.r() * color2.r(),
		      color1.g() * color2.g(),
		      color1.b() * color2.b() );
}


Color operator*(float factor, const Color& color)
{
	return Color( factor*color.r(), factor*color.g(), factor*color.b() );
}


Color operator*(const Color& color, float factor)
{
	return factor*color;
}


ostream& operator<<(ostream& os, const Color& color)
{
	os << "Color(" << color.r() << ", " << color.g() << ", " << color.b() << ")";
	return os;
}


istream& operator>>(istream& is, Color& color)
{
	char ch;
	string str;
	float r;
	float g;
	float b;

	is >> str >> ch >> r >> ch >> g >> ch >> b >> ch;
	color = Color(r, g, b);

	return is;
}
