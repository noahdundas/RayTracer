#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"
#include "Vector.h"

struct Camera
{
private:

public:
	// Object variables
	float screen_size;
	float density;
	int depth;

	Point e; //Location
	Point c; //Hit point on screen
	Vector w; //Perpendicular unit vector
	Vector v; //Look at
	Vector u; //Sky orientation

	// Sets where the camera is, where it's looking, and its orientation
	void lookAt(Point eye, Point center, Vector up);

	// Overloaded output operator for printing the camera's properties
	friend std::ostream& operator<<(std::ostream& os, const Camera c);

	// Overloaded input operator for creating a camera from file input
	// Format: camera {screen_size 60 density 300 depth 1 location <0, 0, 80> look_at <0,0,0> sky <0,1,0>}
	friend std::istream& operator>>(std::istream& is, Camera& camera);
};

#endif /* CAMERA_H */
