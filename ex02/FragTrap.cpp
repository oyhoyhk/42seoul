#include <iostream>
#include <iomanip>

#include "FragTrap.hpp"

FragTrap::FragTrap()
{
	std::cout << std::setw(15) << "[FragTrap] " << "create!!" << std::endl;
}

FragTrap::FragTrap(const FragTrap& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[FragTrap] " << "copy!!" << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << std::setw(15) << "[FragTrap] " << "delete!!" << std::endl;
}

FragTrap&	FragTrap::operator=(const FragTrap& ref)
{
	_name = ref._name;
    _hitPoints = ref._hitPoints;
    _energyPoints = ref._energyPoints;
    _attackDamage = ref._attackDamage;
	std::cout << std::setw(15) << "[FragTrap] " << "operator=!!" << std::endl;
	return (*this);
}

FragTrap::FragTrap(std::string name)
{
	ClapTrap::_name = name;
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	std::cout << std::setw(15) << "[FragTrap] " << "create!!" << std::endl;
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << std::setw(15) << _name << "'s HiFiveGuys!"<<std::endl;
	std::cout << std::setw(15) << "Hi Five ~!"<<std::endl;
}