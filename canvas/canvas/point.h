#ifndef POINT_H
#define POINT_H

class point
{
public:
	point():
		m_x(0),
		m_y(0){};

	point(int x, int y):
		m_x(x),
		m_y(y){};

	point(const point& p):
		m_x(p.getX()),
		m_y(p.getY()){};

	point& operator=(const point& rhs)
	{
		m_x = rhs.getX();
		m_y = rhs.getY();
	};

	bool operator==(const point& rhs)
	{
		return (m_x == rhs.getX() && m_y == rhs.getY());
	};

	int getX() const { return m_x; };
	int getY() const { return m_y; };

private:
	int m_x;
	int m_y;

};


#endif // !POINT_H

