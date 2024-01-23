#ifndef MESH_H
#define MESH_H

#include "Triangle.h"
#include "Hit.h"
#include "Ray.h"
#include "Shape.h"
#include "Sphere.h"
#include <vector>
#include <string>

// A 3D model composed of many triangles to create a complex shape
class Mesh : public Shape
{
private:
	// Object variables
	std::vector<Triangle> triangles; // The array of triangles that composes the mesh
	Sphere bound; 					 // A bounding sphere to increase rendering efficiency
	bool smooth;					 // Whether or not to smooth the edges of adjacent triangles
	bool sphericalMask;				 // Whether to apply masks in spherical form - can improve visual readability of image masks
public:
	// Default destructor
	~Mesh(){};

	// Determines where a given ray intersects with the mesh
	Hit intersect(Ray ray);

	// Overloaded input operator for reading a mesh from a file
	// Format: mesh {source { maps/file.pov flat spherical } scale 50 translate vector finish { <material> } pigment { image_map { ppm maps/file.ppm } } normal { none } mask { none }}
	friend std::istream& operator>>(std::istream& is, Mesh& m);

	// Overloaded output operator for printing the mesh's information
	friend std::ostream& operator<<(std::ostream& os, const Mesh m);
};

#endif /* MESH_H */
