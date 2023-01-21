#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap
{
private:
	std::string _name;
public:
	DiamondTrap();
	DiamondTrap(std::string name);
	DiamondTrap(const DiamondTrap& ref);
	~DiamondTrap();

	DiamondTrap&	operator=(const DiamondTrap& ref);

	void	attack(void);
	void	whoAmI(void);

    const   std::string &getName(void) const;
    const   int &getHitPoints(void) const;
    const   int &getEnergyPoints(void) const;
    const   int &getAttackDamage(void) const;
};

std::ostream    &operator<<(std::ostream &out, const DiamondTrap &ref);

#endif
