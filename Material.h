#ifndef MATERIAL_H
#define MATERIAL_H

#include<ostream>
#include<iostream>
#include<cstring>

// Structure to store data about how to render the material of a shape or mesh
struct Material
{
	float ambient;
	float diffuse;
	float specular;
	float phong_size;
	float refraction;
	float ior;
};

// Overloaded input operator for reading material data from a file
// Format: finish { ambient 0.2 diffuse 0.9 specular 0.8 phong_size 90 refraction 0.8 ior 1.33 }
std::istream& operator>>(std::istream& is, Material& color);

#endif /* MATERIAL_H */
