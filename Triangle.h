#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector.h"
#include "Point.h"
#include "Color.h"
#include "Hit.h"
#include "Ray.h"
#include <array>

// This represents a triangle, which is a single part of a larger mesh
class Triangle
{
private:
	// Object variables

	// An array of the three vertices of the triangle
	std::array<Point, 3> pointArray;

	// An array of the normal vectors of each edge of the triangle
	std::array<Vector, 3> normalArray;

	// An array of the colors at each vertex of the triangle - used for meshing & mapping
	std::array<Color, 3> colorArray;

	// A vector perpendicular to the surface of the triangle
	Vector flatN;

	// The color of the triangle
	Color color_;

public:
	// Returns the point at position i in pointArray
	Point vertex(int i);

	// Returns the normal vector at position i in normalArray
	Vector normal(int i);

	// Returns the triangle's flatN normal vector
	Vector normal();

	// Returns the color at position i in colorArray
	Color color(int i);

	// Returns the triangle's color
	Color color();

	// Resizes and translates the triangle
	void resize(float scale, Vector translate);

	// Determines where a given ray intersects with the triangle
	Hit intersect(Ray ray);

	// Overloaded input operator for reading a sphere from a file
	// Format: smooth_triangle { <vertex1>, <normal1>, <vertex2>, <normal2>, <vertex3>, <vertex3> pigment { color rgb <color> } }
	friend std::istream& operator>>(std::istream& is, Triangle& t);

	// Overloaded output operator for printing the triangle's information
	friend std::ostream& operator<<(std::ostream& os, const Triangle t);
};

#endif /* TRIANGLE_H */
