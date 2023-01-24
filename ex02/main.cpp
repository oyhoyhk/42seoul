#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
//#include "PresidentialPardonForm.hpp"
//#include "RobotomyRequestForm.hpp"

int main()
{
	AForm *form1 = new ShrubberyCreationForm("Tree2");
	AForm *form2 = new RobotomyRequestForm("Robot");
	AForm *form3 = new PresidentialPardonForm("President");

	Bureaucrat b1("Hello", 1);
	Bureaucrat b2("World", 149);
	b1.executeForm(*form1);
	std::cout<<std::endl;
	b2.executeForm(*form1);
	std::cout<<std::endl;
	b1.executeForm(*form2);
	std::cout<<std::endl;
	b2.executeForm(*form2);
	std::cout<<std::endl;
	b1.executeForm(*form3);
	std::cout<<std::endl;
	b2.executeForm(*form3);

	delete form1;
	delete form2;
	delete form3;
}