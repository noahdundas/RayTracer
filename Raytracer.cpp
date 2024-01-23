
#include "Raytracer.h"

#include "Scene.h"

#include <string>
#include <vector>
using namespace std;

void Raytracer(const string& dir, const vector<string>& namesList, const string& operation)
{
	for ( const string& name : namesList) {
		if(operation == "render")
		{
			Scene(dir+"/"+name+".pov").render(dir+"/"+name+".ppm");
		}
		else if (operation == "animate")
		{
			Scene(dir+"/"+name+".pov").animate(dir+"/"+name+".ppm", 60);
		}
		else if (operation == "spherical")
		{
			Scene(dir+"/"+name+".pov").animate_spherical(dir+"/"+name+".ppm", 120);
		} else {
			throw std::invalid_argument("Invalid operation!");
		}
	}
}
