#include <iostream>
#include <iomanip>

#include "Point.hpp"

Point::Point() : _x(0), _y(0)
{}

Point::Point(const Point& ref) : _x(ref.getX()), _y(ref.getY())
{}

Point::Point(const float x, const float y) : _x(Fixed(x)), _y(Fixed(y))
{}

Point::Point(const Fixed x, const Fixed y) : _x(x), _y(y)
{}

Point::~Point()
{}

Point&	Point::operator=(const Point& ref)
{
	const_cast<Fixed&>(_x) = ref.getX();
	const_cast<Fixed&>(_y) = ref.getY();
	std::cout  << std::setw(15) << "[Point] " << "operator=!!" << std::endl;
	return (*this);
}

const Fixed&	Point::getX(void) const
{
	return _x;
}
const Fixed&	Point::getY(void) const
{
	return _y; 
}

Point operator-(const Point& p1, const Point& p2) {
  return Point(p1.getX() - p2.getX(), p1.getY() - p2.getY());
}

Fixed operator*(const Point& v1, const Point& v2) {
  return Fixed((v1.getX() * v2.getY()) - v1.getY() * v2.getX());
}

bool operator~(const Fixed& f) {
  return *const_cast<Fixed *>(&f) > Fixed(0);
}

std::ostream& operator<<(std::ostream& o, const Point& p) {
  return o << "( " << p.getX().toFloat() << ", " << p.getY().toFloat() << " )";
}

bool bsp(const Point a, const Point b, const Point c, const Point point) {
  Point ab = a - b;
  Point bp = b - point;

  Point bc = b - c;
  Point cp = c - point;

  Point ca = c - a;
  Point ap = a - point;

  if ((~(ab * bp) && ~(bc * cp) && ~(ca * ap))
    || (!(~(ab * bp)) && !(~(bc * cp)) && !(~(ca * ap))))
    return true;
  return false;
}
