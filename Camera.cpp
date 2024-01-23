#include "Camera.h"
#include <string>

void Camera::lookAt(Point eye, Point center, Vector up)
{
	e = eye;
	c = center;

	Vector vec(e, c);
	v = vec;
	v = unit(v);

	w = v.cross(up);
	w = unit(w);

	u = w.cross(v);
	u = unit(u);

	w = v.cross(u);
	u = w.cross(v);
}

std::ostream& operator<<(std::ostream& os, const Camera c)
{
	os << "Camera: e:" << c.e << ", c:" << c.c << ", u:" << c.u << ", v:" << c.v << ", w:" << c.w;
	return os;
}

std::istream& operator>>(std::istream& is, Camera& camera)
{
	std::string str;

	//screen_size X
	is >> str;
	float ss;
	is >> ss;
	camera.screen_size = ss;

	//density X
	is >> str;
	float den;
	is >> den;
	camera.density = den;

	//depth X
	is >> str;
	float dep;
	is >> dep;
	camera.depth = dep;

	//location <>
	is >> str;
	Point loc;
	is >> loc;
	camera.e = loc;

	//look_at <>
	is >> str;
	Point look;
	is >> look;
	camera.c = look;

	//sky <>
	is >> str;
	Vector sky;
	is >> sky;
	camera.u = sky;
	camera.u = unit(camera.u);

	Vector vec(camera.e, camera.c);
	camera.v = vec;
	camera.v = unit(camera.v);

	camera.w = camera.v.cross(camera.u);
	camera.w = unit(camera.w);

	return is;
}

