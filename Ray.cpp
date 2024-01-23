#include "Ray.h"

Ray::Ray(Point p, Vector d)
{
	orig = p;
	dir = unit(d);
}

Ray::Ray(Point p1, Point p2)
{
	orig = p1;
	dir = unit(Vector(p1, p2));
}

Point Ray::origin() const
{
	return orig;
}

Vector Ray::direction() const
{
	return dir;
}

Point Ray::point(float t)
{
	return orig + (t * dir);
}

std::ostream& operator<<(std::ostream& os, Ray r)
{
	os << "[Ray: " << r.origin() << ", " << r.direction() << "]";
	return os;
}
