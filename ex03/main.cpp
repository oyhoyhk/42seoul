#include "Point.hpp"

bool	bsp(Point const a, Point const b, Point const c, Point const point);
float	sign(Point p1, Point p2, Point p3);

int main()
{	
	std::cout<<bsp(Point(0,0), Point(10, 10), Point(0, 10), Point(1, 3))<<std::endl;
}
//(p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
float	sign(Point p1, Point p2, Point p3)
{
	return ((p1.getX().toFloat() - p3.getX().toFloat()) * (p2.getY().toFloat() - p3.getY().toFloat()))
		 - ((p2.getX().toFloat() -p3.getX().toFloat())* (p1.getY().toFloat() - p3.getY().toFloat()));
}
bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	float	d1, d2, d3;
	bool	has_neg, has_pos;

	d1 = sign(point, a, b);
	d2 = sign(point, b, c);
	d3 = sign(point, c, a);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}
