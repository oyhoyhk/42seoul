#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>

class Form
{
private:
	const std::string _name;
	bool	_isSigned;
	const int _gradeSign;
	const int _gradeExecute;
public:
	Form();
	Form(std::string name, int gradeSign, int gradeExecute);
	Form(const Form& ref);
	~Form();
	Form&	operator=(const Form& ref);

	class GradeTooHighException : public std::exception {
		public :
			const char *what(void) const throw();
	};

	class GradeTooLowException : public std::exception {
		public :
			const char *what(void) const throw();
	};
};

#endif
