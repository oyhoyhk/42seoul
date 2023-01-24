#ifndef FORM_HPP
# define FORM_HPP

#include "Bureaucrat.hpp"
#include <iostream>

class AForm
{
protected:
	const std::string _name;
	const int _gradeSign;
	const int _gradeExecute;
	bool	_signed;
public:
	AForm();
	AForm(std::string name, int gradeSign, int gradeExecute);
	AForm(const AForm& ref);
	virtual ~AForm();
	AForm&	operator=(const AForm& ref);

	void	beSigned(const Bureaucrat &staff);

	const std::string getName(void) const;
	int	getSignGrade(void) const;
	int	getExecuteGrade(void) const;
	bool	getSigned(void) const;

	virtual void	execute(Bureaucrat const &executor) const = 0;
	
	class GradeTooHighException : public std::exception {
		public :
			const char *what(void) const throw();
	};

	class GradeTooLowException : public std::exception {
		public :
			const char *what(void) const throw();
	};
};

std::ostream& operator<<(std::ostream& out, const AForm& form);

#endif
