#include "Point.h"

Point::Point()
{
    x_ = 0;
    y_ = 0;
    z_ = 0;
}

Point::Point(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

float Point::x() const
{
    return x_;
}

float Point::y() const
{
    return y_;
}

float Point::z() const
{
    return z_;
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
    os << "Point(" << point.x() << ", " << point.y() << ", " << point.z() << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Point& point)
{
	char chToken;
	float x;
	float y;
	float z;

	is >> chToken;       // Read the <
	is >> x >> chToken;  // Read point coordinates and comma
	is >> y >> chToken;
	is >> z >> chToken;  // Reads the last coordinate and >

	point = Point(x, y, z);   // Make the color
	return is;
}
