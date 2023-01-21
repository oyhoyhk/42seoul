#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, FragTrap
{
private:
	std::string _name;
public:
	DiamondTrap();
	DiamondTrap(const DiamondTrap& ref);
	~DiamondTrap();

	DiamondTrap&	operator=(const DiamondTrap& ref);
};

#endif
