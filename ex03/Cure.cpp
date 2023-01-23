#include <iostream>

#include "AMateria.hpp"
#include "Cure.hpp"

Cure::Cure()
{
	_type = "cure";
}

Cure::Cure(const Cure& ref)
{
	this->_type = ref._type;
}

Cure::~Cure()
{
}

Cure&	Cure::operator=(const Cure& ref)
{
	this->_type = ref._type;
	return (*this);
}

AMateria* Cure::clone() const
{
	AMateria *result = new Cure();
	std::cout<<"[Cure] clone!!"<<std::endl;
	return result;
}

void	Cure::use(ICharacter& target)
{
	std::cout << "* heals " << target.getName() << "'s wounds. *" << std::endl;
}