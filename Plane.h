#ifndef PLANE_H_
#define PLANE_H_

#include "Vector.h"
#include "Point.h"
#include "Color.h"
#include "Ray.h"
#include "Hit.h"
#include "Shape.h"

// Represents a flat plane
class Plane : public Shape
{
private:
	// Class variables
	Vector normal; 	// A normal vector perpendicular to the plane
	float dist;		// The distance to the surface of the plance from 0, 0, 0
	Color color_;	// The color of the plane
	
public:
	// Determines where a given ray intersects with the plane
	Hit intersect(Ray ray);

	// Overloaded input operator for reading a plane from a file
	// Format: plane {vector float pigment { color rgb <color> } finish { <material> } normal { none } mask { none }}
	friend std::istream& operator>>(std::istream& is, Plane& t);

	// Overloaded output operator for printing the plane's information
	friend std::ostream& operator<<(std::ostream& os, const Plane p);
};


#endif /* PLANE_H_ */
