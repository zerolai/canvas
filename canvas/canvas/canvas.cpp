#include "canvas.h"
#include "point.h"
#include "line.h"
#include "rectangle.h"
#include <iostream>

using namespace std;


canvas::canvas(const int width, const int height)
{
	m_width = width;
	m_height = height;

	if (m_width < 0 || m_height < 0)
	{
		cout << "invalid canvas size - width = " << m_width << ", height = " << m_height;
		m_width = 0;
		m_height = 0;
	}

	pixelPanel = new char*[m_height + 2];
	for (int i = 0; i < m_height + 2; i++)
	{
		pixelPanel[i] = new char[m_width + 3];
		fill_n(pixelPanel[i], m_width + 2, ' ');
		pixelPanel[i][m_width + 2] = '\0'; //last char for end of string char
	}

	//draw horizontal edges
	drawLine(line(point(0, 0), m_width + 2, LineDirection::RIGHT), '-', true);
	drawLine(line(point(0, m_height + 1), m_width + 2, LineDirection::RIGHT), '-', true);
	//draw vertical edges
	drawLine(line(point(0, 1), m_height, LineDirection::DOWN), '|', true);
	drawLine(line(point(m_width + 1, 1), m_height, LineDirection::DOWN), '|', true);
}

canvas::~canvas()
{
	cout << "~canvas " << endl;
	for (int i = 0; i < m_height + 2; i++)
	{
		delete[] pixelPanel[i];
		pixelPanel[i] = NULL;
	}
	delete [] pixelPanel;
	pixelPanel = NULL;
}

bool canvas::drawLine(const line& l, char c, const bool isEdge)
{
	if (!checkLineInCanvas(l, isEdge))
	{
		cout << "drawLine::out of boundary, do nothing" << endl;
		return false;
	}

	int cursorMove(0);
	switch (l.getDirection())
	{
	case LineDirection::UP:
	case LineDirection::LEFT:
		cursorMove = -1;
	case LineDirection::DOWN:
	case LineDirection::RIGHT:
	default:
		cursorMove = 1;
		break;
	}

	switch (l.getDirection())
	{
		// vertical
	case LineDirection::UP:
	case LineDirection::DOWN:
		for (int i=0; i < l.getLength(); i++)
		{
			int index = cursorMove * i;
			pixelPanel[l.getOrigin().getY() + index][l.getOrigin().getX()] = c;
		}
		break;
		//horizontal
	case LineDirection::LEFT:
	case LineDirection::RIGHT:
		for (int i=0; i < l.getLength(); i++)
		{
			int index = cursorMove * i;
			pixelPanel[l.getOrigin().getY()][l.getOrigin().getX() + index] = c;
		}
	default:
		break;
	}

	return true;
}

bool canvas::drawRectangle(const rectangle& r, char c, const bool isEdge)
{
	if (!checkRectangleInCanvas(r, isEdge))
	{
		cout << "drawRectangle::out of boundary, do nothing" << endl;
		return false;
	}

	//draw horizontal lines
	drawLine(line(r.getOrigin(), r.getWidth(), LineDirection::RIGHT), c, isEdge);

	point lowerLeftPoint(r.getOrigin().getX(), r.getOrigin().getY() + r.getHeight() - 1);
	drawLine(line(lowerLeftPoint, r.getWidth(), LineDirection::RIGHT), c, isEdge);

	//draw vertical lines
	drawLine(line(r.getOrigin(), r.getHeight(), LineDirection::DOWN), c, isEdge);

	point upperRightPoint(r.getOrigin().getX() + r.getWidth() - 1, r.getOrigin().getY());
	drawLine(line(upperRightPoint, r.getHeight(), LineDirection::DOWN), c, isEdge);

	return true;
}

bool canvas::fillColor(const point& p, char c)
{
	if (!checkPointInCanvas(p))
	{
		cout << "fillColor::out of boundary, do nothing" << endl;
		return false;
	}

	char currentPixel = pixelPanel[p.getY()][p.getX()];
	if (pixelPanel[p.getY()][p.getX()] == c) return true; //this pixel is same kind already

	bool goUpper(false);
	point upperNextPixel(p.getX(), p.getY() - 1);
	if (checkPointInCanvas(upperNextPixel) &&
		pixelPanel[upperNextPixel.getY()][upperNextPixel.getX()] == currentPixel)
	{
		goUpper = true;
	}

	bool goLower(false);
	point lowerNextPixel(p.getX(), p.getY() + 1);
	if (checkPointInCanvas(lowerNextPixel) &&
		pixelPanel[lowerNextPixel.getY()][lowerNextPixel.getX()] == currentPixel)
	{
		goLower = true;
	}
		
	bool goLeft(false);
	point leftNextPixel(p.getX() - 1, p.getY());
	if (checkPointInCanvas(leftNextPixel) &&
		pixelPanel[leftNextPixel.getY()][leftNextPixel.getX()] == currentPixel)
	{
		goLeft = true;
	}

	bool goRight(false);
	point rightNextPixel(p.getX() + 1, p.getY());
	if (checkPointInCanvas(rightNextPixel) &&
		pixelPanel[rightNextPixel.getY()][rightNextPixel.getX()] == currentPixel)
	{
		goRight = true;
	}

	// update current pixel
	pixelPanel[p.getY()][p.getX()] = c;
	//print();
	
	if (goUpper) fillColor(upperNextPixel, c);
	if (goLower) fillColor(lowerNextPixel, c);
	if (goLeft)  fillColor(leftNextPixel, c);
	if (goRight) fillColor(rightNextPixel, c);

	return true;
}

bool canvas::checkPointInCanvas(const point& p, const bool includeEdge) const
{
	if (includeEdge)
	{
		return (p.getX() >= 0 && p.getX() <= m_width + 1 && p.getY() >= 0 && p.getY() <= m_height + 1);
	}
	return (p.getX() > 0 && p.getX() <= m_width && p.getY() > 0 && p.getY() <= m_height);
}

bool canvas::checkLineInCanvas(const line& l, const bool includeEdge) const
{
	int x(0);
	int y(0);
	
	switch (l.getDirection())
	{
	case LineDirection::DOWN:
		x = l.getOrigin().getX();
		y = l.getOrigin().getY() + l.getLength() - 1;
		break;
	case LineDirection::UP:
		x = l.getOrigin().getX();
		y = l.getOrigin().getY() - l.getLength() + 1;
		break;
	case LineDirection::RIGHT:
		x = l.getOrigin().getX() + l.getLength() - 1;
		y = l.getOrigin().getY();
		break;
	case LineDirection::LEFT:
		x = l.getOrigin().getX() - l.getLength() + 1;
		y = l.getOrigin().getY();
		break;
	default:
		break;
	}

	point end(x, y);
	return (checkPointInCanvas(l.getOrigin(), includeEdge) && checkPointInCanvas(end, includeEdge));
}

bool canvas::checkRectangleInCanvas(const rectangle& r, const bool includeEdge) const
{
	point end(r.getOrigin().getX() + r.getWidth() -1, r.getOrigin().getY() + r.getHeight() - 1);
	return (checkPointInCanvas(r.getOrigin(), includeEdge) && checkPointInCanvas(end, includeEdge));
}

void canvas::print() const
{
	for (int y = 0; y < m_height + 2; y++)
	{
		cout << pixelPanel[y] << endl; 
	}
}