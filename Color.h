// Representation of color as a triple of R/G/B components
// The R/G/B components are in [0.0 -- 1.0]

#ifndef __COLOR_H__
#define __COLOR_H__

#include <ostream>
#include <istream>
using namespace std;

class Color
{

private:
	// Object variables
	float r_;
	float g_;
	float b_;

public:
	// Creates the default color (black)
	Color();

	// Creates a color based on the given R/G/B components
	// R/G/B values greater than 1 are set to 1
	// negative values are not allowed
	Color(float r, float g, float b);

	// Accessors for the individual color components (as real numbers)
	float r() const;
	float g() const;
	float b() const;

	// Returns a grey color represented as a float
	float gray();
};

// A few pre-defined colors
const Color GRAY50 = Color(.5, .5, .5);  // gray ~50% intensity
const Color WHITE  = Color(1, 1, 1);     // gray 100% intensity
const Color BLACK  = Color(0, 0, 0);     // gray 0% intensity
const Color RED    = Color(1, 0, 0);  
const Color GREEN  = Color(0, 1, 0);
const Color BLUE   = Color(0, 0, 1);

//--General color operators--

// Adds two colors component-wise (color3 = color1 + color2)
Color operator+(const Color& color1, const Color& color2);

// Multiplies two colors component-wise (color3 = color1 * color2)
Color operator*(const Color& color1, const Color& color2);

// Scales the components of a color by a factor (color2 = factor*color1;)
Color operator*(float factor, const Color& color);

// Scales the components of a color by a factor (color2 = color1*factor;)
Color operator*(const Color& color, float factor);

// Overloaded output operator for printing the color's information
ostream& operator<<(ostream& os, const Color& c);

// Overloaded input operator for reading a color from a file
// Format: rgb <1, 1, 1>
istream& operator>>(istream& os, Color& c);

#endif
