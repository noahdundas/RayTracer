#ifndef HIT_H
#define HIT_H

#include "Point.h"
#include "Vector.h"
#include "Color.h"
#include "Material.h"

// This structure represents the point at which a ray intersects with an object, and the attributes of the shape at that point
struct Hit
{
	bool valid;
	Point intersect;
	Vector unit;
	float t;
	Color point_color;
	Material point_material;
	float u;
	float v;
};

#endif /* HIT_H */
