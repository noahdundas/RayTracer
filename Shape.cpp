#include "Shape.h"

Shape::~Shape()
{
	delete image;
	delete bump;
	delete mask;
}

Point Shape::center() const
{
	return center_;
}

float Shape::radius() const
{
	return radius_;
}

