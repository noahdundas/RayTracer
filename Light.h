#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"
#include "Color.h"
#include<iostream>
#include<ostream>

class Light
{
private:
	// Object variables
	Point orig; // Origin of the light
	Color col;	// Color of the light

public:
	// Default constructor - makes a white light at 0, 0, 0
	Light();

	// Constructor that creates a light at the given point with the given color
	Light(Point p, Color c);

	// Get methods for the light's variables
	Point position() const;

	Color color() const;
};

// Overloaded output operator for printing the light's information
std::ostream& operator<<(std::ostream& os, const Light& l);

// Overloaded input operator for reading a light from a file
// Format: light_source {<point>, rgb <color>}
std::istream& operator>>(std::istream& is, Light& l);

#endif /* LIGHT_H */
