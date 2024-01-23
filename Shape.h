#ifndef SHAPE_H
#define SHAPE_H

#include "Point.h"
#include "Material.h"
#include "Color.h"
#include "Hit.h"
#include "Ray.h"
#include "Image.h"

// This is the parent class for all other shapes
class Shape
{
private:

public:
	// Class variables
	Point center_;
	float radius_;
	Material material;
	Color color;
	Image* image = nullptr;
	Image* bump = nullptr;
	Image* mask = nullptr;

	// Default destructor
	~Shape();

	// Get methods for class variables
	Point center() const;

	float radius() const;

	// Virtual method to determine if a given array intersects with the shape
	virtual Hit intersect(Ray ray) = 0;
};

#endif /* SHAPE_H */
