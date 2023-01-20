#include <iomanip>
#include "Fixed.hpp"
#include <iostream>

Fixed::Fixed()
{
	_number = 0;
	//std::cout << std::setw(15) << "[Fixed] " << "create!!" << std::endl;
}

Fixed::Fixed(const Fixed& ref)
{
	(*this) = ref;
	//std::cout << std::setw(15) << "[Fixed] " << "copy!!" << std::endl;
}

Fixed::~Fixed()
{
	//std::cout << std::setw(15) << "[Fixed] " << "delete!!" << std::endl;

}

Fixed&	Fixed::operator=(const Fixed& ref)
{
	_number = ref._number;
	//std::cout << std::setw(15) << "[Fixed] " << "operator=!!" << std::endl;
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

bool	operator == (const Fixed &a, const Fixed &b)
{
	return a.toFloat() == b.toFloat();
}

bool operator > (const Fixed &a, const Fixed &b)
{
	return a.toFloat() > b.toFloat();	
}
bool operator < (const Fixed &a, const Fixed &b)
{
	return a.toFloat() < b.toFloat();
}
bool operator >= (const Fixed &a, const Fixed &b)
{
	return a.toFloat() >= b.toFloat();
}
bool operator != (const Fixed &a, const Fixed &b)
{
	return a.toFloat() != b.toFloat();
}

Fixed operator + (const Fixed &a, const Fixed &b)
{
	float result = a.toFloat() + b.toFloat();
	return Fixed(result);
}
Fixed operator - (const Fixed &a, const Fixed &b)
{
	float result = a.toFloat() - b.toFloat();
	return Fixed(result);

}
Fixed operator * (const Fixed &a, const Fixed &b)
{
	float result = a.toFloat() * b.toFloat();
	return Fixed(result);
}
Fixed operator / (const Fixed &a, const Fixed &b)
{
	float result = a.toFloat() / b.toFloat();
	return Fixed(result);
}


Fixed& operator++(Fixed &fixed)
{
	fixed._number += 1;
	return fixed;
}

Fixed operator++(Fixed &fixed, int)
{
	Fixed temp(fixed._number);
	fixed._number += 1;
	return temp;
}

Fixed& operator--(Fixed &fixed)
{
	fixed._number -= 1;
	return fixed;
}

Fixed operator--(Fixed &fixed, int)
{
	Fixed temp(fixed._number);
	fixed._number -= 1;
	return temp;
}

Fixed& Fixed::min(const Fixed &a, const Fixed &b)
{
	return (*const_cast<Fixed *>(&(a.toFloat() > b.toFloat() ? b : a)));
}
Fixed& Fixed::max(const Fixed &a, const Fixed &b)
{
	return (*const_cast<Fixed *>(&(a.toFloat() > b.toFloat() ? a : b)));
}
