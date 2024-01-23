#ifndef SCENE_H
#define SCENE_H

#include "Color.h"
#include "Light.h"
#include "Camera.h"
#include "Sphere.h"
#include "Canvas.h"
#include "Vector.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Hyperboloid.h"
#include "Mesh.h"
#include "Plane.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>

// This class contains the camera, lights, and shapes that will be rendered
class Scene
{
private:
	// Object variables
	Camera camera; 				// The camera
	Color ambient; 				// Ambient light in the scene - if this is 0, anything not otherwise illuminated will be pure black
	std::vector<Light> lights; 	// All the lights in the scene
	std::vector<Shape*> shapes; // All the shapes in the scene
public:
	// Constructor that builds the scene object from a .pov file
	explicit Scene(std::string filename);

	// Destructor
	~Scene();

	// Renders the scene by tracing rays from the camera into the scenes, draws results onto a Canvas, and saves that image into filename
	void render(std::string filename);

	// Returns the color to render that is seen by the given ray, including up to depth number of reflections off other materials
	Color trace(Ray ray, int depth);

	// Finds the closest intersection of any object in the scene to the camera
	Hit findClosestHit(Ray ray, std::vector<Shape*> shapes);

	// Creates a rotating animation by rendering several images while moving the camera around
	void animate(std::string filename, float frames);

	// Creates a spiralling animation by rendering several images while moving the camera around and up
	void animate_spherical(std::string filename, float frames);
};

#endif /* SCENE_H */
