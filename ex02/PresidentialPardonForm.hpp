#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <string>
class PresidentialPardonForm : public AForm
{
private:
	std::string	_target;
public:
	PresidentialPardonForm();
	PresidentialPardonForm(std::string target);
	PresidentialPardonForm(const PresidentialPardonForm& ref);
	~PresidentialPardonForm();

	PresidentialPardonForm&	operator=(const PresidentialPardonForm& ref);

	void	execute(Bureaucrat const &executor) const;
};

#endif
