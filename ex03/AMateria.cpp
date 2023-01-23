#include <iostream>

#include "AMateria.hpp"

AMateria::AMateria()
{
}

AMateria::AMateria(std::string const &type)
{
	_type = type;
}

AMateria::AMateria(const AMateria& ref)
{
	this->_type = ref._type;
}

AMateria::~AMateria()
{
}

AMateria&	AMateria::operator=(const AMateria& ref)
{
	this->_type = ref._type;
	return (*this);
}

std::string const &AMateria::getType() const
{
	return (_type);
}

void AMateria::use(ICharacter& target)
{
	(void) target;
}