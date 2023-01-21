#include <iostream>


#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
	(*this)._hitPoints = 100;
	(*this)._attackDamage = 20;
	(*this)._energyPoints = 50;
	std::cout << "[ScavTrap] " << "create!!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& ref)
{
	*this=ref;
	std::cout << "[ScavTrap] " << "copy!!" << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << "[ScavTrap] " << "delete!!" << std::endl;
}

ScavTrap&	ScavTrap::operator=(const ScavTrap& ref)
{
	this->_name = ref._name;
	this->_attackDamage = ref._attackDamage;
	this->_energyPoints = ref._energyPoints;
	this->_hitPoints = ref._hitPoints;
	std::cout << "[ScavTrap] " << "operator=!!" << std::endl;
	return (*this);
}

ScavTrap::ScavTrap(std::string name)
{
	(*this)._name = name;
	(*this)._hitPoints = 100;
	(*this)._attackDamage = 20;
	(*this)._energyPoints = 50;
	std::cout << "[ScavTrap] created!!" << std::endl;
}

void	ScavTrap::guardGate(void)
{
	if (_energyPoints == 0)
	{
		std::cout<<"Not enough energy..."<<std::endl;
		return ;
	}
	std::cout<<"ScavTrap is now in Gate keeper mode"<<std::endl;
}

void	ScavTrap::attack(void)
{
	std::cout <<"[ScavTrap] " << _name << " attack!!!" << std::endl;
}