#ifndef INPUT_HPP
# define INPUT_HPP

#include <string>
class Input
{
private:
	double	_val;
	bool	_isNumber;
	bool	_isNaN;
	bool	_isInf;
	bool	_isNegative;
public:
	void	setIsNaN();
	bool	getIsNaN() const;
	void	setIsNumber(bool val);
	bool	getIsNumber() const;
	void	setIsInf();
	bool	getIsInf() const;
	void	setIsNegative();
	bool	getIsNegative() const;

	std::string 	toChar() const;
	std::string 	toInt()	const;
	std::string 	toFloat() const;
	std::string 	toDouble() const;

	Input();
	Input(double val);
	Input(const Input& ref);
	~Input();
	
	Input&	operator=(const Input& ref);
};

std::ostream& operator <<(std::ostream& out, const Input &input);

#endif
