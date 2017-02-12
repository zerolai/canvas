#include <iostream>

#include "point.h"
#include "line.h"
#include "rectangle.h"
#include "canvas.h"

using namespace std;

void fillColorTest(canvas& c)
{
	cout << "Test fillColor" << endl;
	int x, y;
	char color(' '), conti('n');
	c.print();
	while (1)
	{
		cout << "x : y : color" << endl;
		cin >> x >> y >> color;
		c.fillColor(point(x, y), color);
		c.print();

		cout << "continue? (y=yes)";
		cin >> conti;
		if (conti != 'y') break;
	}
}

void drawLineTest(canvas& c)
{
	cout << "Test drawLine" << endl;
	int x, y, l, d;
	char conti('n');
	LineDirection dir;
	c.print();
	while (1)
	{
		
		cout << "x : y : length : direction" << endl;
		cout << "UP=0, DOWN=1, LEFT=2, RIGHT=3" << endl;
		cin >> x >> y >> l >> d;

		switch (d)
		{
		case 0:
			dir = LineDirection::UP;
			break;
		case 1:
			dir = LineDirection::DOWN;
			break;
		case 2:
			dir = LineDirection::LEFT;
			break;
		case 3:
			dir = LineDirection::RIGHT;
			break;
		}
		c.drawLine(line(point(x, y), l, dir), 'x');
		c.print();
		cout << "continue? (y=yes)";
		cin >> conti;
		if (conti != 'y') break;
	}

}

void drawRectangleTest(canvas& c)
{
	cout << "Test drawRectangle" << endl;
	int x, y, w, h;
	char conti('n');
	c.print();
	while (1)
	{
		cout << "x : y : width : height" << endl;
		cin >> x >> y >> w >> h;
		c.drawRectangle(rectangle(point(x, y), w, h), 'x', false);
		c.print();
		cout << "continue? (y=yes)";
		cin >> conti;
		if (conti != 'y') break;
	}
}

void waitCommand()
{
	canvas* c_ptr(NULL);

	while (1)
	{
		char command('Q');
		cout << "enter command: ";

		try
		{
			if (cin >> command)
			{
				if (command == 'Q')
				{
					break;
				}
				else if (command == 'C')
				{
					int w(-1), h(-1);
					if (!(cin >> w >> h))
					{
						cout << "invalid command" << endl;
					}
					else if (w < 0 || h < 0)
					{
						cout << "invalid parameter values" << endl;
					}
					else {
						if (c_ptr) delete c_ptr;
						c_ptr = new canvas(w, h);
						if (c_ptr) c_ptr->print();
					}
				}
				else if (command == 'L')
				{
					int x1(-1), y1(-1), x2(-1), y2(-1);
					if (!(cin >> x1 >> y1 >> x2 >> y2))
					{
						cout << "invalid command" << endl;
					}
					else if (c_ptr == NULL)
					{
						cout << "canvas is not created yet." << endl;
					}
					else if (!(x1 == x2 || y1 == y2))
					{
						cout << "line is neither horizontal or vertical." << endl;
						c_ptr->print();
					}
					else if (x1 == x2)
					{
						//vertical line
						if (y1 > y2)
						{
							line vLine(point(x2, y2), y1 - y2 + 1, LineDirection::DOWN);
							c_ptr->drawLine(vLine, 'x');
						}
						else
						{
							line vLine(point(x1, y1), y2 - y1 + 1, LineDirection::DOWN);
							c_ptr->drawLine(vLine, 'x');
						}
						c_ptr->print();
					}
					else
					{
						// horizontal line
						if (x1 > x2)
						{
							line hLine(point(x2, y2), x1 - x2 + 1, LineDirection::RIGHT);
							c_ptr->drawLine(hLine, 'x');
						}
						else
						{
							line hLine(point(x1, y1), x2 - x1 + 1, LineDirection::RIGHT);
							c_ptr->drawLine(hLine, 'x');
						}
						c_ptr->print();
					}
				}
				else if (command == 'R')
				{
					int x1(-1), y1(-1), x2(-1), y2(-1);
					if (!(cin >> x1 >> y1 >> x2 >> y2))
					{
						cout << "invalid command" << endl;
					}
					else if (c_ptr == NULL)
					{
						cout << "canvas is not created yet." << endl;
					}
					else if (x1 <= x2 && y1 <= y2)
					{
						int width = x2 - x1 + 1;
						int height = y2 - y1 + 1;
						rectangle r(point(x1, y1), width, height);
						c_ptr->drawRectangle(r, 'x');
						c_ptr->print();
					}
					else
					{
						cout << "(x1, y1) is not upper left corner" << endl;
					}
				}
				else if (command == 'B')
				{
					int x1(-1), y1(-1);
					char color('\0');
					if (!(cin >> x1 >> y1 >> color))
					{
						cout << "invalid command" << endl;
					}
					else if (c_ptr == NULL)
					{
						cout << "canvas is not created yet." << endl;
					}
					else
					{
						c_ptr->fillColor(point(x1, y1), color);
						c_ptr->print();
					}
				}
				else
				{
					cout << "invalid command" << endl;
				}
			}
			else
			{
				cout << "invalid command" << endl;
			}
		
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		catch (exception& e)
		{
			cout << "invalid command exception, " << e.what() << endl;
		}
	}

	delete c_ptr;
	c_ptr = NULL;
}


int main()
{
	waitCommand();

	/*
	canvas c(20, 4);
	
	line l1(point(1, 2), 6, LineDirection::RIGHT);
	c.drawLine(l1, 'x');
	c.print();
	//cin.get();

	line l2(point(6, 3), 2, LineDirection::DOWN);
	c.drawLine(l2, 'x');
	c.print();
	//cin.get();
	
	rectangle r1(point(14, 1), 5, 3);
	c.drawRectangle(r1, 'o');
	c.print();
	//cin.get();

	
	rectangle r2(point(0, 0), 22, 6);
	c.drawRectangle(r2, 'R', true);
	c.print();
	cin.get();
	

	drawLineTest(c);
	drawRectangleTest(c);
	fillColorTest(c);
	*/
	return 0;
}

