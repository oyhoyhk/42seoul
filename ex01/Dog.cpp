#include <iostream>
#include "Dog.hpp"

Dog::Dog()
{
	_type = "Dog";
	_brain = new Brain();
	std::cout << "[Dog] " << "create!!" << std::endl;
}

Dog::Dog(const Dog& ref)
{
	*this=ref;
	std::cout << "[Dog] " << "copy!!" << std::endl;
}

Dog::~Dog()
{
	delete _brain;
	std::cout << "[Dog] " << "delete!!" << std::endl;
}

Dog&	Dog::operator=(const Dog& ref)
{
	this->_type = ref._type;
	for(int i=0;i<100;i++)
		this->_brain[i] = ref._brain[i];
	std::cout << "[Dog] " << "operator=!!" << std::endl;
	return (*this);
}

void	Dog::makeSound(void) const
{
	std::cout<<"Woof Woof Woof!"<<std::endl;
}
