#ifndef RAY_H
#define RAY_H

#include "Point.h"
#include "Vector.h"
#include<iostream>
#include<ostream>

// Represents a ray with an origin point and a direction
class Ray
{
private:
	// Object variables
	Point orig;
	Vector dir;

public:
	// Constructor to make a ray with a given point and direction
	Ray(Point p, Vector d);

	// Constructor to make a ray going from p1 in the direction of p2
	Ray(Point p1, Point p2);

	// Get methods for object variables
	Point origin() const;
	Vector direction() const;

	// Returns the point on the ray that is t distance from its origin
	Point point(float t);
};

// Overloaded output operator for printing the ray's information
std::ostream& operator<<(std::ostream& os, Ray r);

#endif /* Ray_H */
