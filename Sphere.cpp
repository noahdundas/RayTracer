#include "Sphere.h"
#include <cmath>
#include <string>
#include <iostream>
#include <ostream>
#include <vector>

const float pi = 3.14159265358979323846264338327950288;

Sphere::Sphere()
{
	center_ = Point(0,0,0);
	radius_ = 0;
}

Sphere::Sphere(Point p, float r)
{
	center_ = p;
	radius_ = r;
}

Hit Sphere::intersect(Ray ray)
{
	Hit hit;

	// Formula for finding if a ray intersects a sphere
	float dx = ray.direction().x();
	float dy = ray.direction().y();
	float dz = ray.direction().z();

	float sx = ray.origin().x();
	float sy = ray.origin().y();
	float sz = ray.origin().z();

	float cx = center_.x();
	float cy = center_.y();
	float cz = center_.z();

	float r = radius_;

	float a = (dx*dx + dy*dy + dz*dz);

	float b = (2*sx*dx + -2*dx*cx + 2*sy*dy + -2*dy*cy + 2*sz*dz + -2*dz*cz);

	float c = (sx*sx + -2*sx*cx + cx*cx + sy*sy + -2*sy*cy + cy*cy + sz*sz + -2*sz*cz + cz*cz - r*r);

	float answerNum = (b*b - 4*a*c);

	if(answerNum < 0)
	{
		hit.valid = false;
		return hit;
	}

	// If the ray intersects the sphere, it will intersect at one or two points, so we need to find the closest point to the camera
	hit.valid = true;
	float t1 = (-b + std::sqrt(answerNum)) / (2*a);
	float t2 = (-b - std::sqrt(answerNum)) / (2*a);
	std::vector<float> t;
	if(t1 > 0 && (t1 < t2 || t2 < 0))
	{
		t.push_back(t1);
		if(t2 > 0)
		{
			t.push_back(t2);
		}
	}
	else if(t2 > 0 && (t2 < t1 || t1 < 0))
	{
		t.push_back(t2);
		if(t1 > 0)
		{
			t.push_back(t1);
		}
	}
	else
	{
		hit.valid = false;
		return hit;
	}

	// Find and set the hit properties
	float tmin = t[0];
	Point p = ray.point(tmin);
	hit.intersect = p;
	texel_uv(hit.intersect, hit.u, hit.v);

	if(!isVisible(hit))
	{
		if(t.size() > 1)
		{
			Point pOther = ray.point(t[1]); 
			hit.intersect = pOther;
			texel_uv(hit.intersect, hit.u, hit.v);
			
			if(!isVisible(hit))
			{
				hit.valid = false;
				return hit;
			}

			tmin = t[1];
		}
		else
		{
			hit.valid = false;
			return hit;
		}
	}

	hit.t = tmin;
	Vector n = unit(Vector(center_, p));
	hit.unit = n;
	hit.unit = bumpNormal(hit);
	hit.intersect = hit.intersect + (hit.unit*0.001);
	hit.point_color = selectColor(hit);
	hit.point_material = material;

	return hit;
}

Color Sphere::selectColor(Hit hit)
{
	if(image == nullptr)
	{
		return color;
	}

	Color c = image->rgb(hit.u, hit.v);
	return c;
}

Vector Sphere::bumpNormal(Hit hit)
{
	if(bump == nullptr)
	{
		return hit.unit;
	}

	Vector n = hit.unit;
	Vector y(0,1,0);
	y = unit(y);
	Vector vu = y.cross(n);
	Vector vv = n.cross(vu);
	vu = n.cross(vv);

	int i = hit.u * bump->image_width;
	int j = hit.v * bump->image_height;

	float du = 0;
	float dv = 0;
	bump->gradient(i, j, du,dv);

	Vector final = n + du*vu + dv*vv;

	return final;
}

bool Sphere::isVisible(Hit hit)
{
	if(mask == nullptr)
	{
		return true;
	}

	float gray = mask->gray(hit.u, hit.v);
	if(gray > 0)
	{
		return true;
	}

	return false;
}

void Sphere::texel_uv(Point p, float& u, float& v)
{
		float px = p.x() - center_.x();
		float py = p.y() - center_.y();
		float pz = p.z() - center_.z();

		float r = std::sqrt(px*px + py*py + pz*pz);
		float phi = std::acos(py/r);
		float theta = std::atan(px/pz);

		v = phi / pi;
		u = (theta + pi) / (2 * pi);
}

std::ostream& operator<<(std::ostream& os, const Sphere s)
{
	os << "[Sphere: " << s.center() << ", " << s.radius() << "]";
	return os;
}

std::istream& operator>>(std::istream& is, Sphere& s)
{
	char ch;
	std::string str;
	Point p;
	float r;
	Color c;
	Material m;

	//  center  ,  radius pigment {   color/image_map
	is >> p >> ch >> r >> str >> ch >> str;

	s = Sphere(p, r);

	if(str == "color")
	{
		// rgb<rgb>  }
		is >> c >> ch;
	}
	else if(str == "image_map")
	{
		//     {   ppm   filename  }    }
		is >> ch >> str >> str >> ch >> ch;
		Image* i = new Image(str);
		s.image = i;
	}

	//  material
	is >> m;

	s.color = c;
	s.material = m;

	//   normal  {  bump_map/none
	is >> str >> ch >> str;

	if(str == "bump_map")
	{
		//    {     ppm  filename  }    }
		is >> ch >> str >> str >> ch >> ch;
		Image* b = new Image(str);
		s.bump = b;
	}
	else if (str == "none")
	{
		//    }
		is >> ch;
	}

	//    mask   {  image_map/none
	is >> str >> ch >> str;

	if(str == "image_map")
	{
		//    {     ppm  filename  }    }
		is >> ch >> str >> str >> ch >> ch;
		Image* b = new Image(str);
		s.mask = b;
	}
	else if (str == "none")
	{
		//    }
		is >> ch;
	}

	return is;
}
