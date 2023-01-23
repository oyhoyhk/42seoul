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
	Point(const Fixed x, const Fixed y);

	Point&	operator=(const Point& ref);
	const Fixed&	getX(void) const;
	const Fixed&	getY(void) const;

};

Point operator-(const Point& p1, const Point& p2);
Fixed operator*(const Point& v1, const Point& v2);
bool bsp(Point const a, Point const b, Point const c, Point const point);
bool operator~(const Fixed& f);
std::ostream& operator<<(std::ostream& o, const Point& p);

#endif
