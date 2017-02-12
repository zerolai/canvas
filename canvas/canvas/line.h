#ifndef LINE_H
#define LINE_H

#include "point.h"

enum LineDirection
{
	UP, DOWN, LEFT, RIGHT
};

class line
{
public:
	line(point origin, int length, LineDirection direction) :
		m_origin(origin),
		m_length(length),
		m_direction(direction){};
	//~line()

	point getOrigin() const { return m_origin; }
	int getLength() const { return m_length; };
	LineDirection getDirection() const { return m_direction; };

private:
	point m_origin;
	int m_length;
	LineDirection m_direction;
	
};

#endif // !LINE_H

