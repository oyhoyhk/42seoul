#include <iostream>
#include "Animal.hpp"

Animal::Animal()
{
	_type = "No Type";
	std::cout << "[Animal] " << "create!!" << std::endl;
}

Animal::Animal(const Animal& ref)
{
	*this=ref;
	std::cout << "[Animal] " << "copy!!" << std::endl;
}

Animal::~Animal()
{
	std::cout << "[Animal] " << "delete!!" << std::endl;
}

Animal&	Animal::operator=(const Animal& ref)
{
	this->_type =ref._type;
	std::cout << "[Animal] " << "operator=!!" << std::endl;
	return (*this);
}

std::string	Animal::getType(void) const
{
	return _type;
}

void	Animal::makeSound(void) const
{
	std::cout << "What is the type of this Animal?" << std::endl;
}
