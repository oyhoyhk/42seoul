#include <iostream>

#include "AMateria.hpp"
#include "Ice.hpp"

Ice::Ice()
{
	_type = "ice";
}

Ice::Ice(const Ice& ref)
{
	this->_type = ref._type;
}

Ice::~Ice()
{
}

Ice&	Ice::operator=(const Ice& ref)
{
	this->_type = ref._type;
	return (*this);
}

AMateria* Ice::clone() const
{
	AMateria *result = new Ice();
	return result;
}

void	Ice::use(ICharacter &target)
{
	std::cout<<"* shoots can ice bolt at "<< target.getName() <<"*"<<std::endl;
}