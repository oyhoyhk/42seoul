#include <cstdlib>
#include <iostream>

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() {
	*const_cast<std::string*>(&this->_name) = "PresidentialPardonForm";
	*const_cast<int*>(&this->_gradeSign) = 25;
	*const_cast<int*>(&this->_gradeExecute) = 5;
	this->_signed = false;
	std::cout << "[PresidentialPardonForm] " << "create!!" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(std::string target)  {
	*const_cast<std::string*>(&this->_name) = target;
	*const_cast<int*>(&this->_gradeSign) = 72;
	*const_cast<int*>(&this->_gradeExecute) = 45;
	this->_signed = false;
	std::cout << "[PresidentialPardonForm] " << "create!!" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& ref)  {
	*const_cast<std::string*>(&this->_name) = ref.getName();
	*const_cast<int*>(&this->_gradeSign) = ref.getSignGrade();
	*const_cast<int*>(&this->_gradeExecute) = ref.getExecuteGrade();
	this->_signed = ref.getSigned();
	std::cout << "[PresidentialPardonForm] " << "copy!!" << std::endl;
}

PresidentialPardonForm::~PresidentialPardonForm() {
	std::cout << "[PresidentialPardonForm] " << "delete!!" << std::endl;
}

PresidentialPardonForm&	PresidentialPardonForm::operator=(const PresidentialPardonForm& ref) {
	if (this != &ref) {
		*const_cast<std::string*>(&this->_name) = ref._name;
		*const_cast<int*>(&this->_gradeSign) = ref._gradeSign;
		*const_cast<int*>(&this->_gradeExecute) = ref._gradeExecute;
		_signed = ref._signed;
	}
	std::cout << "[PresidentialPardonForm] " << "operator=!!" << std::endl;
	return (*this);
}

void	PresidentialPardonForm::execute(Bureaucrat const &executor) const {
	try {
		if (executor.getGrade() > this->getExecuteGrade()) throw AForm::GradeTooLowException();
		std::cout << getName() << " has been pardoned by Zaphod Beeblebrox" <<std::endl;
		std::cout << executor.getName() << " executed " << (*this).getName() << std::endl;
	}
	catch (AForm::GradeTooLowException &e) {
		std::cout << "Failed to be pardoned, because " << e.what() << std::endl;
	}
}