#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap 
{
private:
    std::string _name;
    int _hitPoints;
    int _energyPoints;
    int _attackDamage;
public:
    ScavTrap();
    ScavTrap(const ScavTrap& ref);
    ~ScavTrap();

    ScavTrap&	operator=(const ScavTrap& ref);

    ScavTrap(std::string name);
    void    guardGate();
};

#endif
