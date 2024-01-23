#ifndef CYLINDER_H
#define CYLINDER_H

#include "Point.h"
#include "Material.h"
#include "Color.h"
#include "Hit.h"
#include "Ray.h"
#include "Shape.h"
#include <iostream>

// Represents a cylinder shape
class Cylinder : public Shape
{
private:

public:
	// Object variable
	float height_;

	// Default destructor
	~Cylinder(){};

	// Get methods for the Cylinder's variables
	float height();

	// Determines if a given ray intersects with the cylinder
	Hit intersect(Ray ray);

	// Overloaded input operator for reading a cylinder from a file
	// Format: cylinder { <10, 0, -50>, 15, 20 pigment { <color> } finish { <material> }}
	friend istream& operator>>(std::istream& is, Cylinder& c);
};

#endif /* CYLINDER_H */
