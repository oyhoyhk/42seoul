#include <iostream>
#include "Fixed.hpp"
#include <iomanip>

int main( void )
{
	Fixed a;
	std::cout << a.toInt() << '\n';
	std::cout<<a.toFloat()<<std::endl;
	std::cout<<sizeof(int)<<std::endl;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	Fixed c(b);
	std::cout << std::setw(15) << "a : " << a << std::endl;
	std::cout << std::setw(15) << "++a : " << ++a << std::endl;
	std::cout << std::setw(15) << "a : " << a << std::endl;
	std::cout << std::setw(15) << "a++ : " << a++ << std::endl;
	std::cout << std::setw(15) << "a : " << a << std::endl;
	std::cout << std::setw(15) << "b : " << b << std::endl;
	std::cout << std::setw(15) << "c-- : " << c-- << std::endl;
	std::cout << std::setw(15) << "--c : " << --c << std::endl;
	std::cout << std::setw(15) << "max : " << Fixed::max( a, b ) << std::endl;
	std::cout << std::setw(15) << "min : " << Fixed::min( a, b ) << std::endl;
	return 0;
}

