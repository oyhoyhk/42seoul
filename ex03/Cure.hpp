#ifndef CURE_HPP
# define CURE_HPP

#include "AMateria.hpp"

class Cure : public AMateria
{
private:
	/* data */

public:
	Cure();
	Cure(const Cure& ref);
	~Cure();

	Cure&	operator=(const Cure& ref);
	AMateria* clone() const;
	void use(ICharacter& target);
};

#endif
