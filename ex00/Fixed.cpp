#include <iostream>
#include <iomanip>

#include "Fixed.hpp"


Fixed::Fixed() : _number(0)
{
	std::cout << std::setw(15) << "[Fixed] " << "create!!" << std::endl;
}

Fixed::Fixed(const Fixed& ref)
{
	_number = ref._number;
	std::cout << std::setw(15) << "[Fixed] " << "copy!!" << std::endl;
}

Fixed::~Fixed()
{
	std::cout << std::setw(15) << "[Fixed] " << "delete!!" << std::endl;
}

Fixed&	Fixed::operator=(const Fixed& ref)
{
	Fixed *temp = new Fixed();
	temp->_number = ref._number;
	std::cout << std::setw(15) << "[Fixed] " << "operator=!!" << std::endl;
	return (*temp);
}

int		Fixed::getRawBits(void) const
{
	return (_number);
}

void	Fixed::setRawBits(int const raw)
{
	_number = raw;
}

