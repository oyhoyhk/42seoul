#include "Point.hpp"


int main()
{	
	Point a(0.0, 0.0);
	Point b(15.0, 0);
	Point c(0, 15);

	Point p1(1.1, 1.1);
	Point p2(14.4, 14.4);

	std::cout<<"Point a > " << a << std::endl;
	std::cout<<"Point b > " << b << std::endl;
	std::cout<<"Point c > " << c << std::endl<<std::endl;

	std::cout<<"Point p1 > " << p1 << std::endl;
	std::cout<<"Point p2 > " << p2 << std::endl<<std::endl;

	std::cout<<"BSP(p1) : "<<bsp(a, b ,c, p1) <<std::endl;
	std::cout<<"BSP(p2) : "<<bsp(a, b, c, p2) <<std::endl;
}