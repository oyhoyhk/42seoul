#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
class ShrubberyCreationForm : public AForm
{
private:
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(std::string target);
	ShrubberyCreationForm(const ShrubberyCreationForm& ref);
	~ShrubberyCreationForm();

	void	execute(Bureaucrat const &executor) const;
	ShrubberyCreationForm&	operator=(const ShrubberyCreationForm& ref);
	void	draw(std::string target) const;
};

#endif
