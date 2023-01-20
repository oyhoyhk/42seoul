#include <iostream>
#include <iomanip>

#include "Point.hpp"

Point::Point() : _x(0), _y(0)
{
	std::cout << std::setw(15) << "[Point] " << "create!!" << std::endl;
}

Point::Point(const Point& ref)
{
	*this = ref;
	std::cout << std::setw(15) << "[Point] " << "copy!!" << std::endl;
}

Point::Point(const float x, const float y) : _x(Fixed(x)), _y(Fixed(y))
{
 	std::cout << std::setw(15) << "[Point] " << "create!!" << std::endl;
}

Point::~Point()
{
	std::cout << std::setw(15) << "[Point] " << "delete!!" << std::endl;
}

Point&	Point::operator=(const Point& ref)
{
	ref._x.toFloat();
	std::cout  << std::setw(15) << "[Point] " << "operator=!!" << std::endl;
	return (*this);
}

Fixed	Point::getX(void)
{
	return Fixed(_x);
}
Fixed	Point::getY(void)
{
	return Fixed(_y);
}