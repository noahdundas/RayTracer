#include "Triangle.h"

#include <iostream>
#include <ostream>
#include <string>
#include <cmath>

Point Triangle::vertex(int i)
{
	return pointArray[i];
}

Vector Triangle::normal(int i)
{
	return normalArray[i];
}

Vector Triangle::normal()
{
	return flatN;
}

Color Triangle::color(int i)
{
	return colorArray[i];
}

Color Triangle::color()
{
	return color_;
}

void Triangle::resize(float scale, Vector translate)
{
	for(int i = 0 ; i <= 2 ; i++)
	{
		Point p = vertex(i);
		Vector v(p.x(), p.y(), p.z());
		v = (v*scale) + translate;
		Point pNew(v.x(), v.y(), v.z());
		pointArray[i] = pNew;
	}
}

Hit Triangle::intersect(Ray ray)
{
	Hit hit;

	Point v0 = vertex(0);
	Point v1 = vertex(1);
	Point v2 = vertex(2);
	Point o = ray.origin();
	Vector vec0(v0.x(), v0.y(), v0.z());
	Vector vec1(v1.x(), v1.y(), v1.z());
	Vector vec2(v2.x(), v2.y(), v2.z());
	Vector vecO(o.x(), o.y(), o.z());
	Vector e1(vec1 - vec0);
	Vector e2(vec2 - vec0);
	Vector t(vecO - vec0);
	Vector d = unit(ray.direction());
	Vector p = d.cross(e2);
	Vector q = t.cross(e1);

	float pe1 = dot(p, e1);

	if(pe1 == 0)
	{
		hit.valid = false;
		return hit;
	}

	float factor = 1 / pe1;

	float tdist = factor * dot(q, e2);

	if(tdist <= 0.0000001)
	{
		hit.valid = false;
		return hit;
	}

	float u = factor * dot(p, t);
	float v = factor * dot(q, d);

	if(!(u >= 0 && v >= 0 && u+v <= 1))
	{
		hit.valid = false;
		return hit;
	}

	hit.valid = true;
	hit.u = u;
	hit.v = v;
	hit.t = tdist;
	hit.unit = unit(flatN);
	hit.intersect = ray.point(tdist) + (hit.unit*0.001);
	hit.point_color = color_;

	return hit;
}

std::istream& operator>>(std::istream& is, Triangle& t)
{
	char ch;
	std::string str;
	Point vertex;
	Vector normal;
	Color c;

	//    {
	is >> ch;
	//     V1   ,   N1
	is >> vertex >> ch;
	is >> normal >> ch;
	t.pointArray[0] = vertex;
	t.normalArray[0] = normal;

	is >> vertex >> ch;
	is >> normal >> ch;
	t.pointArray[1] = vertex;
	t.normalArray[1] = normal;

	is >> vertex >> ch;
	is >> normal;
	t.pointArray[2] = vertex;
	t.normalArray[2] = normal;

	//  pigment  {    color   c     }     }
	is >> str >> ch >> str >> c >> ch >> ch;
	t.color_ = c;

	Vector v1(t.vertex(1), t.vertex(2));
	Vector v2(t.vertex(2), t.vertex(0));

	t.flatN = unit(v1.cross(v2));

	Point p0 = t.pointArray[0];
	Vector vec0(p0.x(), p0.y(), p0.z());
	vec0 = unit(vec0);

	Point p1 = t.pointArray[1];
	Vector vec1(p1.x(), p1.y(), p1.z());
	vec1 = unit(vec1);

	Point p2 = t.pointArray[2];
	Vector vec2(p2.x(), p2.y(), p2.z());
	vec2 = unit(vec2);

	Color c0(std::abs(vec0.x()), std::abs(vec0.y()), std::abs(vec0.z()));
	t.colorArray[0] = c0;
	Color c1(std::abs(vec1.x()), std::abs(vec1.y()), std::abs(vec1.z()));
	t.colorArray[1] = c1;
	Color c2(std::abs(vec2.x()), std::abs(vec2.y()), std::abs(vec2.z()));
	t.colorArray[2] = c2;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Triangle t)
{
	os << "Triangle:" << std::endl;
	os << t.pointArray[0] << ", " << t.pointArray[1] << ", " << t.pointArray[2] << std::endl;
	os << t.normalArray[0] << ", " << t.normalArray[1] << ", " << t.normalArray[2] << std::endl;
	os << t.flatN;
	os << t.colorArray[0] << ", " << t.colorArray[1] << ", " << t.colorArray[2] << std::endl;
	os << t.color_;

	return os;
}
