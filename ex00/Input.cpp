#include <exception>
#include <iostream>
#include <string>
#include <limits>

#include "Input.hpp"

Input::Input() {
}

Input::Input(double val) : _isNumber(true) {
	_val = val;
	if (val < 0)
		setIsNegative();
	if (_val != 0 && _val * 2 == _val)
		setIsInf();
}

Input::Input(const Input& ref) {
	this->_val = ref._val;
}

Input::~Input() {
}

Input&	Input::operator=(const Input& ref) {
	this->_val = ref._val;
	return (*this);
}

std::string	Input::toChar() const {
	int val = static_cast<int>(_val);
	if (getIsInf() || getIsNaN() || val < 0 || val > 127)
		return "impossible";
	char ch = static_cast<char>(val);
	if (std::isprint(val))
		return std::string(1, ch);
	else
		return "Non displayable";
}

std::string		Input::toInt()	const {
	if (getIsNaN() || !getIsNumber()) return "impossible";
	if (getIsInf() && !getIsNegative()) return "inf";
	if (getIsInf() && getIsNegative()) return "-inf";
	if (_val > std::numeric_limits<int>::max()) return "inf";
	if (_val < std::numeric_limits<int>::min()) return "-inf";
	return std::to_string(static_cast<int>(_val));
}

std::string	Input::toFloat() const {
	if (!getIsNumber()) return "impossible";
	if (getIsNaN()) return "nanf";
	if (getIsInf() && !getIsNegative()) return "inff";
	if (getIsInf() && getIsNegative()) return "-inff";
	if (_val > std::numeric_limits<float>::max()) return "inff";
	if (_val < std::numeric_limits<float>::max() * -1) return "-inff";
	std::string result = std::to_string(_val);
	return  result.substr(0, result.length() - 5) + "f";
}

std::string	Input::toDouble() const {
	if (!getIsNumber()) return "impossible";
	if (getIsNaN()) return "nan";
	if (getIsInf() && !getIsNegative()) return "inf";
	if (getIsInf() && getIsNegative()) return "-inf";
	std::string result = std::to_string(_val);
	return  result.substr(0, result.length() - 5);
}

void	Input::setIsNumber(bool val) {
	_isNumber = val;
}

bool	Input::getIsNumber() const {
	return _isNumber;
}

void	Input::setIsNaN() {
	_isNaN = true;
}

bool	Input::getIsNaN() const {
	return _isNaN;
}

void	Input::setIsInf() {
	_isInf = true;
}

bool	Input::getIsInf() const {
	return _isInf;
}

void	Input::setIsNegative() {
	_isNegative = true;
}

bool	Input::getIsNegative() const {
	return _isNegative;
}

std::ostream& operator <<(std::ostream& out, const Input &input) {
	out << "char: " << input.toChar() << std::endl;
	out << "int: " << input.toInt() << std::endl;
	out << "float: " << input.toFloat() << std::endl;
	out << "double: " << input.toDouble() << std::endl;
	return out;
}