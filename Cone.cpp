#include "Cone.h"
#include <cmath>
#include <string>
#include <vector>

float Cone::height()
{
	return height_;
}

float Cone::xRadius()
{
	return xRadius_;
}

float Cone::zRadius()
{
	return zRadius_;
}

Hit Cone::intersect(Ray ray)
{
	Hit hit;

	float dx = ray.direction().x();
	float dy = ray.direction().y();
	float dz = ray.direction().z();

	float sx = ray.origin().x();
	float sy = ray.origin().y();
	float sz = ray.origin().z();

	float cx = center_.x();
	float cy = center_.y();
	float cz = center_.z();

	float rx = xRadius_;
	float rz = zRadius_;
	float h = height_;

	float a = ((dx*dx)/(rx*rx) - (dy*dy)/(h*h) + (dz*dz)/(rz*rz));

	float b = ((2*sx*dx)/(rx*rx) - (2*dx*cx)/(rx*rx) - (2*sy*dy)/(h*h) + (2*dy*cy)/(h*h) + (2*sz*dz)/(rz*rz) - (2*dz*cz)/(rz*rz));

	float c = ((sx*sx)/(rx*rx) - (2*sx*cx)/(rx*rx) + (cx*cx)/(rx*rx) - (sy*sy)/(h*h) + (2*sy*cy)/(h*h) - (cy*cy)/(h*h) + (sz*sz)/(rz*rz) - (2*sz*cz)/(rz*rz) + (cz*cz)/(rz*rz));

	float answerNum = (b*b - 4*a*c);

	if(answerNum < 0)
	{
		hit.valid = false;
		return hit;
	}

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

	float tmin = t[0];
	Point p = ray.point(tmin);

	if(p.y() > center_.y() || p.y() < (center_.y()-height_))
	{
		if(t.size() > 1)
		{
			Point pOther = ray.point(t[1]);
			float bottomEdge = center_.y() - height_/2;
			
			if(p.y() < bottomEdge && pOther.y() > bottomEdge) 
			{
				float t3 = (height_/2 - sz) / dz;
				tmin = t3;

				Point p = ray.point(tmin);

				hit.valid = true;
				hit.intersect = p;
				Point nCenter(center_.x(), center_.y(), center_.z());
				Point nBottom(center_.x(), bottomEdge, center_.z());
				hit.unit = unit(Vector(nCenter, nBottom));
				hit.t = tmin;				
				hit.point_color = color;
				hit.point_material = material;

				return hit;				
			}

			if(pOther.y() > center_.y() || pOther.y() < (center_.y()-height_))
			{
				hit.valid = false;
				return hit;
			}

			tmin = t[1];
			p = pOther;
		}
		else
		{
			hit.valid = false;
			return hit;
		}
	}

	float nx = (p.x()-center_.x())/(rx*rx);
	float ny = -(p.y()-center_.y())/(h*h);
	float nz = (p.z()-center_.z())/(rz*rz);
	Vector n(nx, ny, nz);

	hit.unit = unit(n);
	hit.intersect = p + (hit.unit*0.001);
	hit.t = tmin;
	hit.point_color = color;
	hit.point_material = material;

	return hit;
}

istream& operator>>(std::istream& is, Cone& c)
{
	char ch;
	std::string str;
	Point p;
	float h;
	float rx;
	float rz;
	Color col;
	Material mat;

	is >> p >> ch >> rx >> ch >> h >> ch >> rz >> str >> ch >> str >> col >> ch >> mat;

	c.center_ = p;
	c.xRadius_ = rx;
	c.zRadius_ = rz;
	c.height_ = h;
	c.color = col;
	c.material = mat;

	return is;
}
