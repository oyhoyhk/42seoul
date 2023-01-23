#include <iostream>

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	_type = "No type";
	std::cout << "[WrongAnimal] " << "create!!" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& ref)
{
	*this=ref;
	std::cout << "[WrongAnimal] " << "copy!!" << std::endl;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "[WrongAnimal] " << "delete!!" << std::endl;
}

WrongAnimal&	WrongAnimal::operator=(const WrongAnimal& ref)
{
	this->_type = ref._type;
	std::cout << "[WrongAnimal] " << "operator=!!" << std::endl;
	return (*this);
}

void	WrongAnimal::makeSound(void) const
{
	std::cout << "I don't know the type of this animal, Something is wrong" << std::endl;
}
