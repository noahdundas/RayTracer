
#ifndef RAYTRACER_
#define RAYTRACER_

#include "Scene.h"

#include <string>
#include <vector>
using namespace std;

// Given a directory with .pov files and a list of .pov names
// Saves a rendering of each provided .pov scene in a matching .ppm file
// for example: Raytracer("scenes", {"scene1", "scene2", "scene3"});
void Raytracer(const string& dir, const vector<string>& namesList, const string& operation);

#endif
