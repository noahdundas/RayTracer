#include "Mesh.h"

#include <ostream>
#include <string>
#include <ostream>
#include <iostream>
#include <fstream>
#include <limits>

Hit Mesh::intersect(Ray ray)
{
	float nearestT = std::numeric_limits<float>::max();
	Hit hit;

	Hit temp = bound.intersect(ray);
	if(temp.valid == false)
	{
		hit.valid = false;
		return hit;
	}

	for(Triangle t : triangles)
	{
		Hit tempHit = t.intersect(ray);
		if(tempHit.valid == true && tempHit.t < nearestT && tempHit.t >= 0.00001)
		{
			nearestT = tempHit.t;

			if(smooth == true)
			{
				// Color c0 = t.color(0) * tempHit.u;
				// Color c1 = t.color(1) * tempHit.v;
				// Color c2 = t.color(2) * (1 - tempHit.u - tempHit.v);
				// tempHit.point_color = c0 + c1 + c2;

				Vector start = tempHit.unit;

				Vector n1 = t.normal(1) * tempHit.u;
				Vector n2 = t.normal(2) * tempHit.v;
				Vector n0 = t.normal(0) * (1 - tempHit.u - tempHit.v);
				tempHit.unit = unit(n0 + n1 + n2);

				Vector end = tempHit.unit;
			}

			if(image != nullptr)
			{
				if(sphericalMask == true)
				{
					Ray texRay(tempHit.intersect, tempHit.unit);
					Hit texHit = bound.intersect(texRay);
					tempHit.point_color = image->rgb(texHit.u, texHit.v);
				}
				else
				{
					tempHit.point_color = image->rgb(tempHit.u, tempHit.v);
				}
			}

			hit = tempHit;
		}
	}

	hit.point_material = material;

	return hit;
}

std::istream& operator>>(std::istream& is, Mesh& m)
{
	char ch;
	std::string str;
	std::string filename;
	std::string boolSmooth;
	std::string boolMask;

	//   source  {     filename  flat/smooth  direct/spherical  }
	is >> str >> ch >> filename >> boolSmooth >> boolMask >> ch;

	if(boolSmooth == "smooth")
	{
		m.smooth = true;
	}
	else
	{
		m.smooth = false;
	}

	if(boolMask == "spherical")
	{
		m.sphericalMask = true;
	}
	else
	{
		m.sphericalMask = false;
	}

	std::ifstream ifs;
	ifs.open(filename, std::ios::binary);

	if(!ifs.is_open())
	{
		std::cout << "Error! File could not be opened." << std::endl;
	}

	std::string string;
	while(ifs >> string)
	{
		Triangle t;
		if(string == "smooth_triangle")
		{
			ifs >> t;
			m.triangles.push_back(t);
		}
		else
		{
			break;
		}
	}
	ifs.close();

	float scale;
	//   scale   float
	is >> str >> scale;

	Vector translate;
	// translate vector
	is >> str >> translate;

	for(Triangle& t : m.triangles)
	{
		t.resize(scale, translate);
	}

	Material mat;
	//  material
	is >> mat;

	m.material = mat;

	//  pigment {  color/image_map
	is >> str >> ch >> str;

	if(str == "color")
	{
		Color c;
		// rgb<rgb>  }
		is >> c >> ch;
	}
	else if(str == "image_map")
	{
		//     {   ppm   filename  }    }
		is >> ch >> str >> str >> ch >> ch;
		Image* i = new Image(str);
		m.image = i;
	}

	//   normal  {  bump_map/none
	is >> str >> ch >> str;

	if(str == "bump_map")
	{
		//    {     ppm  filename  }    }
		is >> ch >> str >> str >> ch >> ch;
		Image* b = new Image(str);
		m.bump = b;
	}
	else if (str == "none")
	{
		//    }
		is >> ch;
	}

	//    mask   {  image_map/none
	is >> str >> ch >> str;

	if(str == "image_map")
	{
		//    {     ppm  filename  }    }
		is >> ch >> str >> str >> ch >> ch;
		Image* b = new Image(str);
		m.mask = b;
	}
	else if (str == "none")
	{
		//    }
		is >> ch;
	}


	float minX = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float minY = std::numeric_limits<float>::max();
	float maxY = std::numeric_limits<float>::min();
	float minZ = std::numeric_limits<float>::max();
	float maxZ = std::numeric_limits<float>::min();

	for(Triangle t : m.triangles)
	{
		for(int i = 0 ; i <= 2 ; i++)
		{
			if(t.vertex(i).x() < minX)
			{
				minX = t.vertex(i).x();
			}
			else if(t.vertex(i).x() > maxX)
			{
				maxX = t.vertex(i).x();
			}

			if(t.vertex(i).y() < minY)
			{
				minY = t.vertex(i).y();
			}
			else if(t.vertex(i).y() > maxY)
			{
				maxY = t.vertex(i).y();
			}

			if(t.vertex(i).z() < minZ)
			{
				minZ = t.vertex(i).z();
			}
			else if(t.vertex(i).z() > maxZ)
			{
				maxZ = t.vertex(i).z();
			}
		}
	}

	Point maxPoint(maxX, maxY, maxZ);
	Point minPoint(minX, minY, minZ);
	float meanX = (maxX + minX) / 2;
	float meanY = (maxY + minY) / 2;
	float meanZ = (maxZ + minZ) / 2;

	Point boundCenter(meanX, meanY, meanZ);
	Vector boundCorners(minPoint, maxPoint);
	float boundR = boundCorners.length() / 2;

	Sphere s(boundCenter, boundR);

	m.bound = s;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Mesh m)
{
	os << "Mesh:" << std::endl;
	os << "vertices " << m.triangles.size()*3 << std::endl;
	os << m.color << std::endl;
	for(Triangle t : m.triangles)
	{
		os << t << std::endl;
	}

	return os;
}
