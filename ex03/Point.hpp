#ifndef POINT_HPP
# define POINT_HPP

#include "Fixed.hpp"
#include <iostream>
#include <cmath>

class Point
{
private:
	const Fixed _x;
	const Fixed _y;
	
public:
	Point();
	Point(const Point& ref);
	~Point();
	Point(const float x, const float y);

	Point&	operator=(const Point& ref);
	Fixed	getX(void);
	Fixed	getY(void);
};

#endif
