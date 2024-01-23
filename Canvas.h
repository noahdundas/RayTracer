#ifndef CANVAS_H_
#define CANVAS_H_

#include "Color.h"

#include <string>

// Represents the canvas that the rendered image will be drawn on and which will be saved as an image
class Canvas
{
public:
	/**
	 * Creates a canvas of viewable area with range:
	 *     x in [0, w]
	 *     y in [0, h]
	 */
	Canvas(int w, int h);

	/**
	 * Frees the storage used for various buffers.
	 */
	~Canvas();

	/**
	 * Erases the canvas. The view area is set to black.
	 */
	void clear();

	/**
	 * Returns the color of the pixel with the given coordinates (x, y).
	 */
	Color getPixel(int x, int y) const;

	/**
	 * Sets the pixel with the given coordinates (x, y) to the given color c.
	 */
	void setPixel(int x, int y, const Color& c) const;

	/**
	 * Saves a PPM image (in raw, i.e.binary format) to a file with the given name.
	 */
	void saveImage(const std::string& file_name) const;


private:
	/**
	 * Fills in the given color a rectangular region anchored at (w0, h0) and
	 * extending *width* units horizontally and *height* units vertically.
	 */
	void fillRegion(int w0, int h0, int width, int height, const Color& c) const;

	/**
	 * Reserves a 2D array for the color buffer of appropriate size (view + border).
	 */
	void makeCanvas();

	/**
	 * Frees the storage used for the color buffer.
	 */
	void destroyCanvas() const;

private:
	// The width and height of the canvas
	int canvas_width;
	int canvas_height;

	// The color buffer
	Color **image;
}; 

#endif
