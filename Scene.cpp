#include "Scene.h"
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <cstdio>

const float pi = 3.14159265358979323846264338327950288;

Scene::Scene(std::string filename)
{
	std::ifstream ifs(filename);

	std::string token;
	std::string str;

	while(ifs >> token)
	{
		if(token == "light_ambient")
		{
			ifs >> str;
			Color amb;
			ifs >> amb;
			ifs >> str;

			ambient = amb;
		}
		else if(token == "light_source")
		{
			ifs >> str;
			Light l;
			ifs >> l;
			ifs >> str;

			lights.push_back(l);
		}
		else if(token == "camera")
		{
			Camera c;

			ifs >> str;
			ifs >> c;
			ifs >> str;

			camera = c;
		}
		else if(token == "sphere")
		{
			Sphere* sp = new Sphere();
			ifs >> str;
			ifs >> *sp;
			ifs >> str;

			shapes.push_back(sp);
		}
		else if(token == "cylinder")
		{
			Cylinder* cy = new Cylinder();
			ifs >> str;
			ifs >> *cy;
			ifs >> str;

			shapes.push_back(cy);
		}
		else if(token == "cone")
		{
			Cone* co = new Cone();
			ifs >> str;
			ifs >> *co;
			ifs >> str;

			shapes.push_back(co);
		}
		else if(token == "hyperboloid")
		{
			Hyperboloid* hy = new Hyperboloid();
			ifs >> str;
			ifs >> *hy;
			ifs >> str;

			shapes.push_back(hy);
		}
		else if(token == "mesh")
		{
			Mesh* mesh = new Mesh();
			ifs >> str;
			ifs >> *mesh;
			ifs >> str;

			shapes.push_back(mesh);
		}
		else if(token == "plane")
		{
			Plane* pl = new Plane();
			ifs >> str;
			ifs >> *pl;
			ifs >> str;

			std::cout << *pl << std::endl;
			shapes.push_back(pl);
		}
	}
}

Scene::~Scene()
{
	shapes.clear();
}

void Scene::render(std::string filename)
{
	Point center = camera.c;
	float stepUL = camera.screen_size/2;

	Point ul = center + -stepUL*camera.w + stepUL*camera.u;

	Point p = ul;

	Canvas canvas(camera.density, camera.density);

	int canx = 0; 
	int cany = 0;

	float step = camera.screen_size / (camera.density-1);

	for(cany = 0 ; cany < camera.density ; cany++)
	{
		for(canx = 0 ; canx < camera.density ; canx++)
		{
			Ray ray = Ray(camera.e, p);
			Color c = trace(ray, camera.depth);

			canvas.setPixel(canx, cany, c);

			float stepX = canx * step;
			float stepY = cany * step;
			p = ul + stepX*camera.w + -stepY*camera.u;
		}
	}

	canvas.saveImage(filename);
}

Color Scene::trace(Ray ray, int depth)
{
	Hit hit = findClosestHit(ray, shapes);

	if(depth == 0 || hit.valid == false)
	{
		return BLACK;
	}

	Color c = ambient * hit.point_color * hit.point_material.ambient;

	Vector v = -ray.direction();
	Vector n = unit(hit.unit);

	Vector rv = 2 * n * dot(n, v) - v;
	Ray ref(hit.intersect, rv);

	Color reflected = trace(ref, depth-1);

	for(Light light : lights)
	{
		Vector pointToLight(hit.intersect, light.position());
		Ray shadow(hit.intersect, unit(pointToLight)); //unit
		Hit shadowHit = findClosestHit(shadow, shapes);
		float lightDist = pointToLight.length();

		if(shadowHit.valid == false || (shadowHit.valid == true && shadowHit.t > lightDist))
		{
			Vector l(hit.intersect, light.position());
			l = unit(l);

			float product = dot(n, l);

			if(product >= 0.0000001)
			{
				Vector r = 2 * product * n - l;
				c = c + (hit.point_material.diffuse * light.color() * hit.point_color * product); //Diffusion
				c = c + (hit.point_material.specular * light.color() * hit.point_color * std::pow(dot(r, v), hit.point_material.phong_size)); //Specular
			}
		}
	}

	c = c + reflected;

	return c;

}

Hit Scene::findClosestHit(Ray ray, std::vector<Shape*> shapes)
{
	Hit hit;
	hit.t = std::numeric_limits<float>::infinity();
	hit.valid = false;

	for(Shape* shape : shapes)
	{
		Hit tempHit = shape->intersect(ray);
		if(tempHit.valid == true && tempHit.t < hit.t && tempHit.t >= 0.1)
		{
			hit.intersect = tempHit.intersect;
			hit.point_color = tempHit.point_color;
			hit.point_material = tempHit.point_material;
			hit.t = tempHit.t;
			hit.unit = tempHit.unit;
			hit.valid = true;
		}
	}

	return hit;
}

void Scene::animate(std::string filename, float frames)
{
	std::string index = "000";
	char* indexChar = const_cast<char*>(index.c_str());

	float angle = (2*pi) / frames;

	for(int frame = 0 ; frame < frames ; frame++)
	{
		std::string fileBase = filename;
		std::sprintf(indexChar, "%03d", frame);
		fileBase.insert(std::size(filename) - 4,indexChar);

		render(fileBase);

		Point center(0,0,0);
		Vector up(0, 1, 0);

		float xp = camera.e.z()*std::sin(angle) + camera.e.x()*std::cos(angle);
		float yp = camera.e.y();
		float zp = camera.e.z()*std::cos(angle) - camera.e.x()*std::sin(angle);

		Point eye(xp, yp, zp);

		camera.lookAt(eye, center, up);
	}
}

void Scene::animate_spherical(std::string filename, float frames)
{
	std::string index = "000";
	char* indexChar = const_cast<char*>(index.c_str());

	float angleX = (2*pi) / frames;
	float angleY = ((pi) - (pi/6)) / frames;
	Vector rVect(camera.e, camera.c);
	float r = rVect.length();

	for(int frame = 0 ; frame < frames ; frame++)
	{
		Point center(0,0,0);
		Vector up(0, 1, 0);

		float totalAngleX = angleX*frame;
		float totalAngleY = angleY*(frames-frame);

		float xp = r*std::sin(totalAngleX)*std::sin(totalAngleY);
		float yp = r*std::cos(totalAngleY);
		float zp = r*std::cos(totalAngleX)*std::sin(totalAngleY);

		Point eye(xp, yp, zp);

		camera.lookAt(eye, center, up);

		std::string fileBase = filename;
		std::sprintf(indexChar, "%03d", frame);
		fileBase.insert(std::size(filename) - 4,indexChar);

		render(fileBase);
	}
}
