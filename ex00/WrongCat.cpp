#include <iostream>

#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	_type = "Cat";
	std::cout << "[WrongCat] " << "create!!" << std::endl;
}

WrongCat::WrongCat(const WrongCat& ref)
{
	*this=ref;
	std::cout << "[WrongCat] " << "copy!!" << std::endl;
}

WrongCat::~WrongCat()
{
	std::cout << "[WrongCat] " << "delete!!" << std::endl;
}

WrongCat&	WrongCat::operator=(const WrongCat& ref)
{
	this->_type = ref._type;
	std::cout << "[WrongCat] " << "operator=!!" << std::endl;
	return (*this);
}

void	WrongCat::makeSound() const 
{
	std::cout <<"Meow Meow Meow ~ " << std::endl;
}
