#ifndef SPHERE_H
#define SPHERE_H

#include "Point.h"
#include "Ray.h"
#include "Hit.h"
#include "Material.h"
#include "Color.h"
#include "Shape.h"
#include "Image.h"

#include <ostream>
#include <cmath>
#include <cstring>

// Inherits from Shape
class Sphere : public Shape
{
private:

public:
	// Default constructor
	Sphere();

	// Constructor to create a sphere at point p with radus r
	Sphere(Point p, float r);

	// Default destructor
	~Sphere(){};

	// Determines where a given ray intersects with the sphere
	Hit intersect(Ray ray);

	// Gets the color on the sphere at the point of the hit
	Color selectColor(Hit hit);

	// Returns a vector from the hit that is adjusted by the sphere's bump map
	Vector bumpNormal(Hit hit);

	// Calculates if the hit on a sphere is visible when using a transparent image mask
	bool isVisible(Hit hit);

	// Converts a point on the sphere to a set of u,v coordinates on a texture image 
	void texel_uv(Point p, float& u, float& v);

	// Overloaded input operator for reading a sphere from a file
	// Format: sphere {center, radius pigment { <color> } finish { <material> } normal { image } mask { image }}
	friend std::istream& operator>>(std::istream& is, Sphere& s);
};

// Overloaded output operator for printing the sphere's information
std::ostream& operator<<(std::ostream& os, const Sphere s);


#endif /* SPHERE_H */
