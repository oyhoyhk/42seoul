#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed
{
private:
	int			_number;
	static const int 	_fractionalBits = 8;

public:
	Fixed();
	Fixed(const Fixed& ref);
	~Fixed();

	Fixed&	operator=(const Fixed& ref);

	Fixed(const int num);
	Fixed(const float num);
	float	toFloat(void) const;
	int		toInt(void) const;

	Fixed& operator++(void);
	Fixed operator++(int);

	Fixed& operator--(void);
	Fixed operator--(int);
	static	Fixed& min(const Fixed &a, const Fixed &b);
	static	Fixed& max(const Fixed &a, const Fixed &b);
	static	Fixed& min(Fixed &a, Fixed &b);
	static	Fixed& max(Fixed &a, Fixed &b);

	bool operator == (const Fixed &a);
	bool operator > (const Fixed &a);
	bool operator < (const Fixed &a);
	bool operator >= (const Fixed &a);
	bool operator <= (const Fixed &a);
	bool operator != (const Fixed &a);

	Fixed operator + (const Fixed &a) const;
	Fixed operator - (const Fixed &a) const;
	Fixed operator * (const Fixed &a) const;
	Fixed operator / (const Fixed &a) const;
};

std::ostream& operator<<(std::ostream &os, const Fixed &ref);

#endif
