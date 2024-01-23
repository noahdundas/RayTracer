#ifndef VECTOR_H
#define VECTOR_H

#include "Point.h"

// Represents a direction and velocity in 3d space by representing the point x, y, z as a direction in space from 0, 0, 0
class Vector
{
private:
	// Object variables
	float x_;
	float y_;
	float z_;

public:
	// Default constructor
	Vector();

	// Constructor that sets x, y, and z manually
	Vector(float x, float y, float z);

	// Constructor that creates a vector as the difference between two points
	Vector(Point p1, Point p2);

	// Get methods for the vector's variables
	float x() const;

	float y() const;

	float z() const;

	// Returns the squared length of the vector
	float sqr_length() const;

	// Returns the true length of the vector
	float length() const;

	// Overloaded plus operator that returns a new vector that's the sum of this vector and another
	// Usage: v3 = v1 + v2
	Vector operator+(Vector other) const;

	// Overloaded minus operator that returns a new vector that's the difference of this vector and another
	// Usage: v3 = v1 - v2
	Vector operator-(Vector other) const;

	// Overloaded multiplier operator that returns a new vector with this vector's intensity multiplied by alpha
	// Usage: v3 = v1 * v2
	Vector operator*(float alpha) const;

	// Returns the point of the vector's x, y, z coordinates
	Point point();

	// Returns a new vector that is perpendicular to this vector and another
	Vector cross(Vector other);
};

//--General vector operations--

// Returns the dot product of two vectors
float dot(Vector v1, Vector v2);

// Returns a new vector from the given vector that is unit scale - no part of the unit vector can be > 1
Vector unit(Vector vector);

// Overloaded negative operator that returns an inverse vector
// Usage: v2 = -v1
Vector operator-(Vector vector);

// Overloaded division operator that returns a new vector from a given vector divided by alpha
// Usage: v2 = v1/int
Vector operator/(const Vector vector, float alpha);

// Overloaded multiplier operator that returns a new vector with the given vector's intensity multiplied by alpha
// Usage: v2 = int*v1
Vector operator*(float alpha, const Vector vector);

// Returns a new point that is the sum of a given point and a given vector
// Usage: p2 = p1+v1
Point operator+(Point point, Vector vector);

// Overloaded output operator to print the vector's information
std::ostream& operator<<(std::ostream& os, const Vector& vector);

// Overloaded input operator to create a vector from file input
// Format: <0,1,0>
std::istream& operator>>(std::istream& is, Vector& vector);

#endif /* VECTOR_H */
