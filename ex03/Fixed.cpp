#include <iomanip>

#include "Fixed.hpp"

Fixed::Fixed()
{
	_number = 0;
}

Fixed::Fixed(const Fixed& ref)
{
	(*this) = ref;
}

Fixed::~Fixed()
{

}

Fixed&	Fixed::operator=(const Fixed& ref)
{
	_number = ref._number;
	return *this;
}

Fixed::Fixed(const int num)
{
	_number = (num << _fractionalBits);
}

Fixed::Fixed(const float num)
{
	_number = roundf((1 << _fractionalBits) * num);
}

float	Fixed::toFloat(void) const 
{
	return (static_cast<float>(_number) / (1 << _fractionalBits));
}

int		Fixed::toInt(void) const 
{
	return (_number >> _fractionalBits);
}

std::ostream& operator<<(std::ostream &os, const Fixed &ref)
{
	os << ref.toFloat();
	return os;
}

bool	Fixed::operator == (const Fixed &a)
{
	return this->toFloat() == a.toFloat();
}

bool	Fixed::operator > (const Fixed &a)
{
	return this->toFloat() > a.toFloat();
}
bool	Fixed::operator < (const Fixed &a)
{
	return this->toFloat() < a.toFloat();
}
bool Fixed::operator >= (const Fixed &a)
{
	return this->toFloat() >= a.toFloat();
}
bool Fixed::operator <= (const Fixed &a)
{
	return this->toFloat() <= a.toFloat();
}
bool Fixed::operator != (const Fixed &a)
{
	return this->toFloat() == a.toFloat();
}

Fixed Fixed::operator + (const Fixed &a) const
{
	return Fixed(this->toFloat() + a.toFloat());
}
Fixed Fixed::operator - (const Fixed &a) const
{
	return Fixed(this->toFloat() - a.toFloat());

}
Fixed Fixed::operator * (const Fixed &a) const
{
	return Fixed(this->toFloat() * a.toFloat());
}
Fixed Fixed::operator / (const Fixed &a) const
{
	return Fixed(this->toFloat() / a.toFloat());
}


Fixed& Fixed::operator++(void)
{
	(*this)._number += 1;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed temp((*this).toFloat());
	(*this)._number += 1;
	return temp;
}

Fixed& Fixed::operator--(void)
{
	(*this)._number -= 1;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed temp((*this)._number);
	(*this)._number -= 1;
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

Fixed& Fixed::min(Fixed &a, Fixed &b)
{
	return (a.toFloat() > b.toFloat() ? b : a);
}
Fixed& Fixed::max(Fixed &a, Fixed &b)
{
	return (a.toFloat() > b.toFloat() ? a : b);
}