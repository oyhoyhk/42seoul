#include "Point.hpp"


int main()
{	
	Point a(0.0f, 0.0f);
	Point b(15.0f, 0);
	Point c(0, 15);

	Point p1(1.1f, 1.1f);
	Point p2(14.4f, 14.4f);
	Point p3(5, 3);
	Point p4(12.3f, 7.3f);
	Point p5(-1, 2.1);

	std::cout<<"Point a > " << a << std::endl;
	std::cout<<"Point b > " << b << std::endl;
	std::cout<<"Point c > " << c << std::endl<<std::endl;

	std::cout<<"Point p1 > " << p1 << std::endl;
	std::cout<<"Point p2 > " << p2 << std::endl;
	std::cout<<"Point p3 > " << p3 << std::endl;
	std::cout<<"Point p4 > " << p4 << std::endl;
	std::cout<<"Point p5 > " << p5 << std::endl<<std::endl;

	std::cout<<"BSP(p1) : "<< bsp(a, b ,c, p1) <<std::endl;
	std::cout<<"BSP(p2) : "<< bsp(a, b, c, p2) <<std::endl;
	std::cout<<"BSP(p3) : "<< bsp(a, b, c, p3) <<std::endl;
	std::cout<<"BSP(p4) : "<< bsp(a, b, c, p4) <<std::endl;
	std::cout<<"BSP(p5) : "<< bsp(a, b, c, p5) <<std::endl;
}