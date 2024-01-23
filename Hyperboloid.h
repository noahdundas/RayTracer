#ifndef HYPERBOLOID_H
#define HYPERBOLOID_H

#include "Shape.h"

class Hyperboloid : public Shape
{
private:

public:
	// Object variables
	float aHeight_;
	float bHeight_;
	float xRadius_;
	float zRadius_;

	// Default destructor
	~Hyperboloid() {};

	// Access methods for object variables
	float aHeight();

	float bHeight();

	float xRadius();

	float zRadius();

	// Determines if a given ray intersects with the hyperboloid
	Hit intersect(Ray ray);

	// Overloaded input operator for reading a hyperboloid from a file
	// Format: hyperboloid { <10, 10, -50>, 20, 30, 25, 20 pigment { <color> } finish { <material> } }
	friend istream& operator>>(std::istream& is, Hyperboloid& c);
};

#endif /* HYPERBOLOID_H */
