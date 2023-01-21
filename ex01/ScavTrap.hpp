#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
private:
	/* data */

public:
	ScavTrap();
	ScavTrap(std::string name);
	ScavTrap(const ScavTrap& ref);
	~ScavTrap();

	ScavTrap&	operator=(const ScavTrap& ref);

	void	guardGate(void);
};

#endif
