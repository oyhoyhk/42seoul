#include <iostream>

#include "Form.hpp"

Form::Form() : _name(""), _gradeSign(0), _gradeExecute(0)
{
	std::cout << "[Form] " << "create!!" << std::endl;
}

Form::Form(std::string name, int gradeSign, int gradeExecute) : _name(name), _gradeSign(gradeSign), _gradeExecute(gradeExecute)
{
	_isSigned = false;
}

Form::Form(const Form& ref) : _name(ref._name), _gradeExecute(ref._gradeExecute), _gradeSign(ref._gradeSign)
{
	this->_isSigned = ref._isSigned;
	std::cout << "[Form] " << "copy!!" << std::endl;
}

Form::~Form()
{
	std::cout << "[Form] " << "delete!!" << std::endl;
}

Form&	Form::operator=(const Form& ref)
{
	this->_isSigned = ref._isSigned;
	std::cout << "[Form] " << "operator=!!" << std::endl;
	return (*this);
}

const char* Form::GradeTooHighException::what(void) const throw() {
	return "Grade too high...";
}

const char *Form::GradeTooLowException::what(void) const throw() {
	return "Grade too low...";
}

