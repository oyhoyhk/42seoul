#include <exception>
#include <iostream>

#include "Bureaucrat.hpp"
#include "AForm.hpp"

Bureaucrat::Bureaucrat() {
	std::cout << "[Bureaucrat] " << "create!!" << std::endl;
}

void	Bureaucrat::increment(void) {
	try {
		if ((getGrade() - 30 < 1) || getGrade() - 30 > 150)
			throw Bureaucrat::GradeTooHighException();
		_grade -= 30;
		std::cout << *this << std::endl;
	} catch (Bureaucrat::GradeTooHighException &e) {
		std::cout << e.what() << std::endl;
	}
}

void	Bureaucrat::decrement(void) {
	try {
		if ((getGrade() + 30 > 150) || getGrade() + 30 < 1) 
			throw Bureaucrat::GradeTooLowException();
		_grade += 30;
		std::cout << *this << std::endl;
	} catch (Bureaucrat::GradeTooLowException &e) {
		std::cout << e.what() << std::endl;
	}
}

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name) {
	try {
		_grade = grade;
		if (grade < 1)
			throw Bureaucrat::GradeTooHighException();
		else if (grade > 150)
			throw Bureaucrat::GradeTooLowException();
		std::cout<<*this<<std::endl;
	} catch (Bureaucrat::GradeTooHighException &e) {
		std::cout << e.what() << std::endl;
	} catch (Bureaucrat::GradeTooLowException &e) {
		std::cout << e.what() << std::endl;
	}

}

const char *Bureaucrat::GradeTooHighException::what(void) const throw() {
	return "Grade too high...";
}

const char *Bureaucrat::GradeTooLowException::what(void) const throw() {
	return "Grade too low...";
}

Bureaucrat::Bureaucrat(const Bureaucrat& ref) {
	*this=ref;
	std::cout << "[Bureaucrat] " << "copy!!" << std::endl;
}

Bureaucrat::~Bureaucrat() {
	std::cout << "[Bureaucrat] " << "delete!!" << std::endl;
}

Bureaucrat&	Bureaucrat::operator=(const Bureaucrat& ref) {
	this->_grade = ref._grade;
	std::cout << "[Bureaucrat] " << "operator=!!" << std::endl;
	return (*this);
}

std::string Bureaucrat::getName(void) const {
	return this->_name;
}

int Bureaucrat::getGrade(void) const {
	return this->_grade;
}


std::ostream& operator << (std::ostream& out, const Bureaucrat &target) {
	out << target.getName() << ", bureaucrat grade " << target.getGrade();
	return out;
}

void	Bureaucrat::signForm(const AForm& form) const {
	try {
		(*const_cast<AForm*>(&form)).beSigned(*this);
		std::cout << _name << " signs " << form.getName() << std::endl;
	} catch (std::exception &e) {
		std::cerr << _name << " cannot sign " << form.getName() << " because " << e.what() << std::endl;
	}
}

void	Bureaucrat::executeForm(AForm const &form) {
	form.execute(*this);
}