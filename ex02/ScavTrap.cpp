#include <iostream>
#include <iomanip>

#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
    std::cout << std::setw(15) << "[ScavTrap] " << "create!!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& ref)
{
    *this=ref;
    std::cout << std::setw(15) << "[ScavTrap] " << "copy!!" << std::endl;
}

ScavTrap::~ScavTrap()
{
    std::cout << std::setw(15) << "[ScavTrap] " << "delete!!" << std::endl;
}

ScavTrap&	ScavTrap::operator=(const ScavTrap& ref)
{
    _name = ref._name;
    _hitPoints = ref._hitPoints;
    _energyPoints = ref._energyPoints;
    _attackDamage = ref._attackDamage;
    std::cout << std::setw(15) << "[ScavTrap] " << "operator=!!" << std::endl;
    return (*this);
}

ScavTrap::ScavTrap(std::string name)
{
    std::cout << std::setw(15) << "[ScavTrap] " << "create!!" << std::endl;
    _name = name;
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;
}

void   ScavTrap::guardGate()
{
    if (this->_hitPoints <= 0)
    {
        std::cout << std::setw(15) << "[ScavTrap] " << "is broken..." << std::endl;
        return ;
    }
    std::cout << std::setw(15) << "[ScavTrap] " << "has enterred in Gate keeper mode." << std::endl;
}
