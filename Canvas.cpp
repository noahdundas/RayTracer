#include "Canvas.h"
#include "Color.h"

#include <algorithm>
#include <string>
#include <ostream>
#include <fstream>
#include <cassert>

using uchar = unsigned char;

void Canvas::setPixel(int x, int y, const Color& c) const
{
	image[y][x] = c;
}

Color Canvas::getPixel(int x, int y) const
{
	return image[y][x];
}

Canvas::Canvas(int w, int h)
{
	canvas_width = w;
	canvas_height = h;

	makeCanvas();
	clear();
}

Canvas::~Canvas() 
{
	destroyCanvas();
}

void Canvas::clear()
{
	// Set the whole canvas to black
	fillRegion(0, 0, canvas_width, canvas_height, BLACK);
}

void Canvas::saveImage(const std::string& file_name) const
{
	std::ofstream ofs(file_name, std::ios::binary);

	// Write the header information
	ofs << "P6" << std::endl;
	ofs << canvas_width << "\t" << canvas_height << std::endl;
	ofs << 255 << std::endl;

	// Save the image data one row at a time
	for(int y = 0; y < canvas_height; ++y) {
		for(int x = 0; x < canvas_width; ++x) {
			Color c = getPixel(x, y);
			ofs << uchar(255*c.r()) << uchar(255*c.g()) << uchar(255*c.b());
		}
	}
}

void Canvas::makeCanvas()
{
	image = new Color*[canvas_height];
	for(int h = 0; h < canvas_height; ++h) {
		image[h] = new Color[canvas_width];
	}
}

void Canvas::destroyCanvas() const
{
	for(int h = 0; h < canvas_height; ++h) {
		delete [] image[h];
	}
	delete [] image;
}

void Canvas::fillRegion(int w0, int h0, int width, int height, const Color& c) const
{
	int w1 = w0 + width;
	int h1 = h0 + height;

	for(int y = h0; y < h1; ++y) {
		for(int x = w0; x < w1; ++x) {
			setPixel(x, y, c);
		}
	}
}
