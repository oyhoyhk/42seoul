#include <iostream>

#include "AMateria.hpp"
#include "MateriaSource.hpp"
#include "Cure.hpp"
#include "Ice.hpp"


MateriaSource::MateriaSource()
{
	_count = 0;
	for(int i=0;i<4;i++)
		_list[i] = nullptr;
}

MateriaSource::MateriaSource(const MateriaSource& ref)
{
	(void) ref;
}

MateriaSource::~MateriaSource()
{
	for(int i=0;i<4;i++) {
	if (_list[i] != nullptr)
		delete _list[i];
	}
}

MateriaSource&	MateriaSource::operator=(const MateriaSource& ref)
{
	(void) ref;
	return (*this);
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
	AMateria *temp = nullptr;
	if (type == "cure")
		temp = new Cure();	
	else if (type == "ice")
		temp = new Ice();
	return temp;	
}

void	MateriaSource::learnMateria(AMateria *materia)
{
	if (_count == 4)
		return ;
	_list[_count] = materia;
	_count++;
}
