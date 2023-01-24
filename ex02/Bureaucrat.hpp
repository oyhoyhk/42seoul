#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <exception>
#include <iostream>

class AForm;

class Bureaucrat
{
private:
	const std::string _name;
	int	_grade;
public:
	Bureaucrat();
	Bureaucrat(std::string name, int grade);
	Bureaucrat(const Bureaucrat& ref);
	~Bureaucrat();

	Bureaucrat&	operator=(const Bureaucrat& ref);

	std::string getName(void) const;
	int getGrade(void) const;

	void	increment(void);
	void	decrement(void);

	void	signForm(const AForm& form) const;
	void	executeForm(AForm const &form);

	class GradeTooHighException : public std::exception {
		public:
			const char *what(void) const throw();
	};

	class GradeTooLowException : public std::exception {
		public:
			const char *what(void) const throw();
	};
};

std::ostream& operator << (std::ostream& out, const Bureaucrat &target);

#endif
