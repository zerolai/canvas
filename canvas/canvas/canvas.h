#ifndef CANVAS_H
#define CANVAS_H

class point;
class line;
class rectangle;


class canvas
{

public:
	canvas(const int width, const int height);
	canvas(const canvas& c) = delete;
	~canvas();

	int getWidth() const { return m_width; };
	int getHeight() const { return m_height; };

	bool drawLine(const line& l, char c, const bool isEdge = false);
	bool drawRectangle(const rectangle& r, char c, const bool isEdge = false);
	bool fillColor(const point& p, char c);
	
	bool checkPointInCanvas(const point& p, const bool includeEdge = false) const;
	bool checkLineInCanvas(const line& l, const bool includeEdge = false) const;
	bool checkRectangleInCanvas(const rectangle& r, const bool includeEdge = false) const;

	void print() const;

private:
	char** pixelPanel;
	int m_width;
	int m_height;
};

#endif // !CANVAS_H




