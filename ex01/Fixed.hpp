#ifndef FIXED_HPP
# define FIXED_HPP

#include <cmath>
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
};

std::ostream& operator<<(std::ostream &os, const Fixed &ref);

#endif
