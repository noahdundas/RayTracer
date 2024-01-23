#include "Plane.h"
#include "Image.h"
#include <string>
#include <ostream>
#include <iostream>

Hit Plane::intersect(Ray ray)
{
	Hit hit;

	float a = normal.x();
	float b = normal.y();
	float c = normal.z();

	float sx = ray.origin().x();
	float sy = ray.origin().y();
	float sz = ray.origin().z();

	float dx = ray.direction().x();
	float dy = ray.direction().y();
	float dz = ray.direction().z();

	// float denom = dot(normal,ray.direction());

	// if(denom >= 0.0000001){
	// 	Point origin(0,0,0);
	// 	Ray normalRay(origin, normal);
	// 	Point p0 = normalRay.point(dist);
	// 	Vector p0l0(p0, ray.origin());
	// 	float t = dot(p0l0, normal) / denom;
	// 	if (t >= 0)
	// 	{
	// 		hit.valid = true;
	// 		hit.intersect = ray.point(t);
	// 		hit.unit = unit(normal);
	// 		hit.point_color = color_;
	// 		hit.point_material = material;		
	// 	}
	// }

	// hit.valid = false;
	// return hit;
	// Start new
	float divide = (a*dx + b*dy + c*dz);

	if(divide == 0)
	{
		// hit.valid = false;
		// return hit;
	}

	float numerator = -a*sx + -b*sy + -c*sz + -dist;

	float t = numerator / divide;

	if(t == 0)
	{
		// hit.valid = false;
		// return hit;
	}

	hit.valid = true;
	hit.intersect = ray.point(t);
	hit.unit = unit(normal);
	hit.point_color = color_;
	hit.point_material = material;

	return hit;
	// End new
}

std::istream& operator>>(std::istream& is, Plane& p)
{
	char ch;
	std::string str;
	Vector n;
	float d;

	is >> n >> d;

	p.normal = n;
	p.dist = d;

	Color c;
	
	is >> str >> ch >> str >> c >> ch >> ch;
	p.color_ = c;

	Material mat;
		//  material
		is >> mat;

		p.material = mat;

		is >> str >> ch >> str;

		if(str == "bump_map")
		{
			is >> ch >> str >> str >> ch >> ch;
			Image* b = new Image(str);
			p.bump = b;
		}
		else if (str == "none")
		{
			is >> ch;
		}

		is >> str >> ch >> str;

		if(str == "image_map")
		{
			is >> ch >> str >> str >> ch >> ch;
			Image* b = new Image(str);
			p.mask = b;
		}
		else if (str == "none")
		{
			is >> ch;
		}

	return is;
}

std::ostream& operator<<(std::ostream& os, const Plane p)
{
	os << "Plane: " << p.normal << " " << p.dist << " " << p.color_;
	return os;
}
