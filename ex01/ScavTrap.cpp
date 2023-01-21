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
	this->_name = ref._name;
	this->_attackDamage = ref._attackDamage;
	this->_energyPoints = ref._energyPoints;
	this->_hitPoints = ref._hitPoints;
	std::cout << std::setw(15) << "[ScavTrap] " << "operator=!!" << std::endl;
	return (*this);
}

ScavTrap::ScavTrap(std::string name)
{
	(*this)._name = name;
	(*this)._hitPoints = 100;
	(*this)._attackDamage = 20;
	(*this)._energyPoints = 50;
	std::cout << std::setw(15) << "[ScavTrap] created!!" << std::endl;
}

void	ScavTrap::guardGate(void)
{
	if (_energyPoints == 0)
	{
		std::cout<<std::setw(15)<<"Not enough energy..."<<std::endl;
		return ;
	}
	std::cout<<std::setw(15)<<"ScavTrap is now in Gate keeper mode"<<std::endl;
}
