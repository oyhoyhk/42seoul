#include <iostream>
#include "Cat.hpp"

Cat::Cat()
{
	_type = "Cat";
	_brain = new Brain();
	std::cout << "[Cat] " << "create!!" << std::endl;
}

Cat::Cat(const Cat& ref)
{
	*this=ref;
	std::cout << "[Cat] " << "copy!!" << std::endl;
}

Cat::~Cat()
{
	delete _brain;
	std::cout << "[Cat] " << "delete!!" << std::endl;
}

Cat&	Cat::operator=(const Cat& ref)
{
	this->_type = ref._type;
	std::cout << "[Cat] " << "operator=!!" << std::endl;
	return (*this);
}

void	Cat::makeSound() const
{
	std::cout << "Meow Meow Meow ~" << std::endl;
}
