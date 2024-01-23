#include "Material.h"
#include <string>

std::istream& operator>>(std::istream& is, Material& material)
{
	char ch;
	std::string str;
	float a;
	float d;
	float s;
	float p;
	float r;
	float i;

	is >> str >> ch >> str >> a >> str >> d >> str >> s >> str >> p >> str >> r >> str >> i >> ch;

	material.ambient = a;
	material.diffuse = d;
	material.specular = s;
	material.phong_size = p;
	material.refraction = r;
	material.ior = i;

	return is;
}
