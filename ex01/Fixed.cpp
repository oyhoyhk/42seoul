#include <iomanip>

#include "Fixed.hpp"

Fixed::Fixed()
{
	std::cout << std::setw(15) << "[Fixed] " << "create!!" << std::endl;
}

Fixed::Fixed(const Fixed& ref)
{
	(*this) = ref;
	std::cout << std::setw(15) << "[Fixed] " << "copy!!" << std::endl;
}

Fixed::~Fixed()
{
	std::cout << std::setw(15) << "[Fixed] " << "delete!!" << std::endl;

}

Fixed&	Fixed::operator=(const Fixed& ref)
{
	_number = ref._number;
	std::cout << std::setw(15) << "[Fixed] " << "operator=!!" << std::endl;
	return *this;
}

Fixed::Fixed(const int num)
{
	_number = (num << 8);
}

Fixed::Fixed(const float num)
{
	_number = roundf((1 << 8) * num);
}

float	Fixed::toFloat(void) const 
{
	return (static_cast<float>(_number) / (1 << 8));
}

int		Fixed::toInt(void) const 
{
	return (_number >> 8);
}

std::ostream& operator<<(std::ostream &os, const Fixed &ref)
{
	os << ref.toFloat();
	return os;
}