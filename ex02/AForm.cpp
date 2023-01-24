#include <iostream>

#include "AForm.hpp"

AForm::AForm() : _name(""), _gradeSign(0), _gradeExecute(0), _signed(false)
{
	std::cout << "[AForm] " << "create!!" << std::endl;
}

AForm::AForm(std::string name, int gradeSign, int gradeExecute) : _name(name), _gradeSign(gradeSign), _gradeExecute(gradeExecute), _signed(false)
{
	if (_gradeSign < 1 || _gradeExecute < 1)
		throw GradeTooHighException();
	if (_gradeSign > 150 || _gradeExecute > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm& ref) : _name(ref._name),_gradeSign(ref._gradeSign), _gradeExecute(ref._gradeExecute)
{
	this->_signed = ref._signed;
	std::cout << "[AForm] " << "copy!!" << std::endl;
}

AForm::~AForm()
{
	std::cout << "[AForm] " << "delete!!" << std::endl;
}

AForm&	AForm::operator=(const AForm& ref)
{
	if (this == &ref) return *this;
	this->_signed = ref._signed;
	*(const_cast<std::string*>(&_name)) = ref._name;
	*(const_cast<int*>(&_gradeSign)) = ref._gradeSign;
	*(const_cast<int*>(&_gradeExecute)) = ref._gradeExecute;
	std::cout << "[AForm] " << "operator=!!" << std::endl;
	return (*this);
}

const std::string AForm::getName(void) const{
	return _name;
}

int	AForm::getExecuteGrade(void) const {
	return _gradeExecute;
}

int	AForm::getSignGrade(void) const {
	return _gradeSign;
}

bool	AForm::getSigned(void) const {
	return _signed;
}

void	AForm::beSigned(const Bureaucrat &staff) {
	if (staff.getGrade() > _gradeSign) throw AForm::GradeTooLowException();
	_signed = true;
}

const char* AForm::GradeTooHighException::what(void) const throw() {
	return "Grade too high...";
}

const char *AForm::GradeTooLowException::what(void) const throw() {
	return "Grade too low...";
}

std::ostream& operator<<(std::ostream& out, const AForm& form) {
	return out << form.getName() << ", sign grade :  " << form.getSignGrade() << " , exec grade : "
			<< form.getExecuteGrade() << " , signed : " << (form.getSigned() == true ? "YES" : "NO");
}
