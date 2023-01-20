#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed
{
private:
	/* data */
	int			_number;
	static const int 	_fractionalBits;

public:
	Fixed();
	Fixed(const Fixed& ref);
	~Fixed();

	Fixed&	operator=(const Fixed& ref);

	Fixed(const int num);
	Fixed(const float num);
	float	toFloat(void) const;
	int		toInt(void) const;

	friend bool	operator == (const Fixed &a, const Fixed &b);
	friend bool operator > (const Fixed &a, const Fixed &b);
	friend bool operator < (const Fixed &a, const Fixed &b);
	friend bool operator >= (const Fixed &a, const Fixed &b);
	friend bool operator != (const Fixed &a, const Fixed &b);

	friend Fixed operator + (const Fixed &a, const Fixed &b);
	friend Fixed operator - (const Fixed &a, const Fixed &b);
	friend Fixed operator * (const Fixed &a, const Fixed &b);
	friend Fixed operator / (const Fixed &a, const Fixed &b);

	friend Fixed& operator++(Fixed &fixed);
	friend Fixed operator++(Fixed &fixed, int);
	
	friend Fixed& operator--(Fixed &fixed);
	friend Fixed operator--(Fixed &fixed, int);
	

	static	Fixed& min(const Fixed &a, const Fixed &b);
	static	Fixed& max(const Fixed &a, const Fixed &b);
};

std::ostream& operator<<(std::ostream &os, const Fixed &ref);

#endif
