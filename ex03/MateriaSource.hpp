#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

#include "AMateria.hpp"

class MateriaSource : public IMateriaSource
{
private:
	AMateria *_list[4];
	int	_count;
public:
	MateriaSource();
	MateriaSource(const MateriaSource& ref);
	~MateriaSource();

	MateriaSource&	operator=(const MateriaSource& ref);

	void		learnMateria(AMateria *);
	AMateria	*createMateria(std::string const &type);
};

#endif
