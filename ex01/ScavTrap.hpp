#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap 
{
public:
    ScavTrap();
    ScavTrap(const ScavTrap& ref);
    ~ScavTrap();

    ScavTrap&	operator=(const ScavTrap& ref);

    ScavTrap(std::string name);
    void    guardGate();
    void    attack(const std::string& target);
};

#endif
