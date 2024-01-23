#ifndef CONE_H
#define CONE_H

#include "Shape.h"

// Represents a cone shape
class Cone : public Shape
{
private:

public:
	// Object variables
	float height_;
	float xRadius_;
	float zRadius_;

	// Default destructor
	~Cone() {};

	// Get methods for the cone's variables
	float height();

	float xRadius();

	float zRadius();

	// Determines if a given ray intersects with the cone
	Hit intersect(Ray ray);

	// Overloaded input operator for reading a cone from a file
	// Format: cone {<10, 15, -50>, 20, 30, 20 pigment { <color> } finish { <material> }} 
	friend istream& operator>>(std::istream& is, Cone& c);
};

#endif /* CONE_H */
