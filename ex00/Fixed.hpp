#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed
{
private:
	/* data */
	int					_number;
	static const int	_frationalBits = 8;
public:
	Fixed();
	Fixed(const Fixed& ref);
	~Fixed();

	Fixed&	operator=(const Fixed& ref);
	int		getRawBits(void) const;
	void	setRawBits(int const raw);
};

#endif
