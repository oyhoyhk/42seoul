#include <iostream>

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() {
	*const_cast<std::string*>(&this->_name) = "RobotomyRequestForm";
	*const_cast<int*>(&this->_gradeSign) = 72;
	*const_cast<int*>(&this->_gradeExecute) = 45;
	this->_signed = false;
	std::cout << "[RobotomyRequestForm] " << "create!!" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(std::string target) {
	*const_cast<std::string*>(&this->_name) = target;
	*const_cast<int*>(&this->_gradeSign) = 72;
	*const_cast<int*>(&this->_gradeExecute) = 45;
	this->_signed = false;
	std::cout << "[PresidentialPardonForm] " << "create!!" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& ref) {
	*const_cast<std::string*>(&this->_name) = ref.getName();
	*const_cast<int*>(&this->_gradeSign) = ref.getSignGrade();
	*const_cast<int*>(&this->_gradeExecute) = ref.getExecuteGrade();
	this->_signed = ref._signed;
	std::cout << "[RobotomyRequestForm] " << "copy!!" << std::endl;
}

RobotomyRequestForm::~RobotomyRequestForm() {
	std::cout << "[RobotomyRequestForm] " << "delete!!" << std::endl;
}

RobotomyRequestForm&	RobotomyRequestForm::operator=(const RobotomyRequestForm& ref) {
	*const_cast<std::string*>(&this->_name) = ref.getName();
	*const_cast<int*>(&this->_gradeSign) = ref.getSignGrade();
	*const_cast<int*>(&this->_gradeExecute) = ref.getExecuteGrade();
	this->_signed = ref._signed;
	std::cout << "[RobotomyRequestForm] " << "operator=!!" << std::endl;
	return (*this);
}

void RobotomyRequestForm::execute(const Bureaucrat &executor) const {
	try {
		if (executor.getGrade() > this->getExecuteGrade()) throw AForm::GradeTooLowException();
		srand(time(nullptr));
		int val = rand() % 2;
		if (val == 1) {
			std::cout << getName() << " : DRRRRRRRRrrrrrrrrrrrrrrrr" <<std::endl;
		} else {
			std::cout << getName() << " Robotomize failed..." << std::endl;
		}
		std::cout << executor.getName() << " executed " << (*this).getName() << std::endl;
	}
	catch (AForm::GradeTooLowException &e) {
		std::cout << "Failed to excute robotomize, because " << e.what() <<std::endl;
	}
}