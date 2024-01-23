#ifndef IMAGE_H
#define IMAGE_H

#include "Color.h"
#include <string>

// An image, represented by a 2D array of colors
class Image
{
private:
	// The image variable
	Color **image;

	// Internal method to get the color of a color point in the image
	Color intget(int i, int j);

	// Internal method to interpolate the color in between adjacent colors in the image
	Color fltget(float i, float j);
public:
	// Width and height variables for the image
	int image_width;
	int image_height;

	// Constructor
	explicit Image(std::string filename);

	// Destructor
	~Image();

	// Saves the image to a file
	void saveImage(std::string filename);

	// Returns the color at any point in the image
	Color rgb(float u, float v);

	// Returns a color that is a mix of two given colors at the given alpha percentage
	// For example, lerp(0.5, RED, YELLOW) would produce a shade of orange that is equally red and yellow
	Color lerp(float alpha, Color c0, Color c1);
	
	// Adjusts the du and dv directions based on the gradient of the image (used for bump map masks)
	void gradient(float u, float v, float& du, float& dv);

	// Calculates the severity of the bump map adjustment based on the greyscale factor of the image at point u, v
	float gray(float u, float v);
};

#endif /* IMAGE_H */
