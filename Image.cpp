#include "Image.h"
#include <string>
#include <string>
#include <ostream>
#include <iostream>
#include <fstream>
#include <ios>
#include <cmath>

using uchar = unsigned char;

Image::Image(std::string filename)
{
	std::ifstream ifs;
	ifs.open(filename, std::ios::binary);

	if(!ifs.is_open())
	{
		std::cout << "Error! File could not be opened." << std::endl;
	}

	std::string str;
	ifs >> str; 	//Reads P6
	int w;
	int h;
	int max;
	ifs >> w >> h; 	//Reads width and height
	ifs >> max;		//Reads max color value

	//Get Image info
	image_width = w;
	image_height = h;

	ifs.ignore(256, '\n');   // Will remove the '\n' after 255
	ifs >> noskipws;         // Will ensure spaces are not skipped

	//Create Image canvas
	image = new Color*[image_width];

	for(int h = 0; h < image_width; ++h)
	{
		image[h] = new Color[image_height];
	}

	//Fill in canvas
	for(int y = 0 ; y < image_height ; ++y)
	{
		for(int x = 0 ; x < image_width ; ++x)
		{
			uchar r;
			uchar g;
			uchar b;

			ifs >> r >> g >> b; 	// Reads in the rgb color for each pixel in the image

			float fr = (float)r / max;
			float fg = (float)g / max;
			float fb = (float)b / max;

			Color c(fr, fg, fb);
			image[x][y] = c;
		}
	}

	ifs.close();
}

Image::~Image()
{
	delete image;
}

void Image::saveImage(std::string filename)
{
	std::ofstream ofs(filename, std::ios::binary);

	// Write the header information
	ofs << "P6" << std::endl;
	ofs << image_width << "\t" << image_height << std::endl;
	ofs << 255 << std::endl;

	// Save the image data one row at a time
	// Go in reverse direction, so the top row is first in the file
	for(int y = 0; y < image_height; ++y) {
		for(int x = 0; x < image_width; ++x) {
			Color c = image[x][y];
			ofs << uchar(255*c.r()) << uchar(255*c.g()) << uchar(255*c.b());
		}
	}
}

Color Image::rgb(float u, float v)
{
	float i = u * image_width;
	float j = v * image_height;
	return fltget(i,j);
}

Color Image::intget(int i, int j)
{
	int intI = (i + image_width) % image_width;
	int intJ = (j + image_height) % image_height;
	return image[intI][intJ];
}

Color Image::fltget(float i, float j)
{
	int ifloor = std::floor(i);
	int jfloor = std::floor(j);

	float i0 = i - ifloor;
	float j0 = j - jfloor;
	float i1 = 1 - i0;
	float j1 = 1 - j0;

	Color ll = intget(ifloor, jfloor);
	Color lr = intget(ifloor+1, jfloor);
	Color ul = intget(ifloor, jfloor+1);
	Color ur = intget(ifloor, jfloor+1);

	Color c1 = j0 * ul + j1 * ll;
	Color c2 = j0 * ur + j1 * lr;
	Color c = i0 * c2 + i1 * c1;

	return c;
}

Color Image::lerp(float alpha, Color c0, Color c1)
{
	return c0*(1-alpha) + c1*(alpha);
}

float Image::gray(float u, float v)
{
	Color c = rgb(u, v);
	float result = c.r()*0.299 + c.g()*0.587 + c.b()*0.114;
	return result;
}

void Image::gradient(float u, float v, float& du, float& dv)
{
	du = (intget(u + 1, v).gray() - intget(u - 1, v).gray()) / 2;
	dv = (intget(u, v + 1).gray() - intget(u, v - 1).gray()) / 2;
}
