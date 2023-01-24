#include <exception>
#include <iostream>
#include <fstream>

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() {
	std::cout << "[ShrubberyCreationForm] " << "create!!" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) {
	*const_cast<std::string*>(&this->_name) = target;
	*const_cast<int*>(&this->_gradeSign) = 145;
	*const_cast<int*>(&this->_gradeExecute) = 137;
	this->_signed = false;
	std::cout << "[ShrubberyCreationForm] " << "create!!" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& ref) {
	*this=ref;
	std::cout << "[ShrubberyCreationForm] " << "copy!!" << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	std::cout << "[ShrubberyCreationForm] " << "delete!!" << std::endl;
}

ShrubberyCreationForm&	ShrubberyCreationForm::operator=(const ShrubberyCreationForm& ref) {
	if (this != &ref) {
		*const_cast<std::string*>(&this->_name) = ref._name;
		*const_cast<int*>(&this->_gradeSign) = ref._gradeSign;
		*const_cast<int*>(&this->_gradeExecute) = ref._gradeExecute;
		_signed = ref._signed;
	}
	std::cout << "[ShrubberyCreationForm] " << "operator=!!" << std::endl;
	return (*this);
}

void	ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
	try {
		if (executor.getGrade() > this->getExecuteGrade()) throw AForm::GradeTooLowException();
		draw(getName());
		std::cout << executor.getName() << " executed " << (*this).getName() << std::endl;
	}
	catch (AForm::GradeTooLowException &e) {
		std::cout << "Failed to draw, because " << e.what() <<std::endl;
	}
}

void	ShrubberyCreationForm::draw(std::string target) const {
	try {
		std::cout << target << std::endl;
		std::cout<<target + "_shrubbery"<<std::endl;
		std::ofstream out(target + "_shrubbery");
		out << "					 _{\\ _{\\{\\/}/}/}__" << std::endl;
		out << "					{/{/\\}{/{/\\}(\\}{/\\} _" << std::endl;
		out << "				{/{/\\}{/{/\\}(_)\\}{/{/\\}  _" << std::endl;
		out << "				{\\{/(\\}\\}{/{/\\}\\}{/){/\\}\\} /\\}" << std::endl;
		out << "			{/{/(_)/}{\\{/)\\}{\\(_){/}/}/}/}" << std::endl;
		out << "			_{\\{/{/{\\{/{/(_)/}/}/}{\\(/}/}/}" << std::endl;
		out << "			{/{/{\\{\\{\\(/}{\\{\\/}/}{\\}(_){\\/}\\}" << std::endl;
		out << "			_{\\{/{\\{/(_)\\}/}{/{/{/\\}\\})\\}{/\\}" << std::endl;
		out << "			{/{/{\\{\\(/}{/{\\{\\{\\/})/}{\\(_)/}/}\\}" << std::endl;
		out << "			{\\{\\/}(_){\\{\\{\\/}/}(_){\\/}{\\/}/})/}" << std::endl;
		out << "			{/{\\{\\/}{/{\\{\\{\\/}/}{\\{\\/}/}\\}(_)" << std::endl;
		out << "			{/{\\{\\/}{/){\\{\\{\\/}/}{\\{\\(/}/}\\}/}" << std::endl;
		out << "			{/{\\{\\/}(_){\\{\\{\\(/}/}{\\(_)/}/}\\}" << std::endl;
		out << "				{/({/{\\{/{\\{\\/}(_){\\/}/}\\}/}(\\}" << std::endl;
		out << "				(_){/{\\/}{\\{\\/}/}{\\{\\)/}/}(_)" << std::endl;
		out << "				{/{/{\\{\\/}{/{\\{\\{\\(_)/}" << std::endl;
		out << "					{/{\\{\\{\\/}/}{\\{\\\\}/}" << std::endl;
		out << "					{){/ {\\/}{\\/} \\}\\}" << std::endl;
		out << "					(_)  \\.-'.-/" << std::endl;
		out << "				__...--- |'-.-'| --...__" << std::endl;
		out << "		 _...--\"   .-'   |'-.-'|  ' -.  ""--..__" << std::endl;
		out << "  		-\"   ' .  . '    |.'-._| '  . .  '   " << std::endl;
		out << "		. '-  '    .--'  | '-.'|    .  '  . '" << std::endl;
		out << "				' ..     |'-_.-|" << std::endl;
		out << "		.  '  .       _.-|-._ -|-._  .  '  ." << std::endl;
		out << "					.'   |'- .-|   '." << std::endl;
		out << "		..-'   ' .  '.   `-._.-�   .'  '  - ." << std::endl;
		out << "		.-' '        '-._______.-'     '  ." << std::endl;
		out << "			.      ~," << std::endl;

	} catch (std::exception &e) {
		std::cout<<e.what()<<std::endl;
	}
		
}