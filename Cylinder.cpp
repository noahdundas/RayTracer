#include "Cylinder.h"
#include "Color.h"
#include <string>
#include <cmath>
#include <vector>

float Cylinder::height()
{
	return height_;
}

Hit Cylinder::intersect(Ray ray)
{
	Hit hit;

	float dx = ray.direction().x();
	float dz = ray.direction().z();

	float sx = ray.origin().x();
	float sz = ray.origin().z();

	float cx = center_.x();
	float cz = center_.z();

	float r = radius_;

	float a = (dx*dx + dz*dz);

	float b = (2*sx*dx + -2*dx*cx + 2*sz*dz + -2*dz*cz);

	float c = (sx*sx + -2*sx*cx + cx*cx + sz*sz + -2*sz*cz + cz*cz - r*r);

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

	float topEdge = center_.y() + height_/2;
	float bottomEdge = center_.y() - height_/2;

	if(p.y() > topEdge || p.y() < bottomEdge)
	{
		if(t.size() > 1)
		{
			Point pOther = ray.point(t[1]); 
			
			if (p.y() > topEdge && pOther.y() < topEdge)
			{
				float t3 = (height_/2 - sz) / dz;
				tmin = t3;
				
				Point p = ray.point(tmin);

				hit.valid = true;				
				hit.intersect = p;
				Point nCenter(center_.x(), center_.y(), center_.z());
				Point nTop(center_.x(), topEdge, center_.z());
				hit.unit = unit(Vector(nCenter, nTop));
				hit.t = tmin;				
				hit.point_color = color;
				hit.point_material = material;

				return hit;	
			} 
			else if(p.y() < bottomEdge && pOther.y() > bottomEdge) 
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

			if(pOther.y() > topEdge || pOther.y() < bottomEdge)
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

	hit.intersect = p;
	Point nCenter(center_.x(), p.y(), center_.z());
	hit.unit = unit(Vector(nCenter, p));
	hit.t = tmin;
	hit.point_color = color;
	hit.point_material = material;

	return hit;
}

istream& operator>>(std::istream& is, Cylinder& c)
{
	char ch;
	std::string str;
	Point p;
	float h;
	float r;
	Color col;
	Material mat;

	is >> p >> ch >> r >> ch >> h >> str >> ch >> str >> col >> ch >> mat;

	c.center_ = p;
	c.radius_ = r;
	c.height_ = h;
	c.color = col;
	c.material = mat;

	return is;
}
