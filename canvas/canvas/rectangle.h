#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"

class rectangle
{
public:
	rectangle(point origin, int width, int height) :
		m_origin(origin),
		m_width(width),
		m_height(height) {};

	point getOrigin() const { return m_origin; };
	int getWidth() const { return m_width; };
	int getHeight() const { return m_height; };
private:
	point m_origin;
	int m_width;
	int m_height;
};
#endif // !RECTANGLE_H

