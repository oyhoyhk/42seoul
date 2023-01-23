#ifndef ICE_HPP
# define ICE_HPP

#include "AMateria.hpp"

class Ice : public AMateria
{
private:
	/* data */

public:
	Ice();
	Ice(const Ice& ref);
	~Ice();

	Ice&	operator=(const Ice& ref);

	AMateria* clone() const;
	void use(ICharacter& target);
};

#endif
