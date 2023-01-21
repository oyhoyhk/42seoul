#include <iostream>


#include "FragTrap.hpp"

FragTrap::FragTrap()
{
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	std::cout << "[FragTrap] " << "create!!" << std::endl;
}

FragTrap::FragTrap(const FragTrap& ref)
{
	*this=ref;
	std::cout << "[FragTrap] " << "copy!!" << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "[FragTrap] " << "delete!!" << std::endl;
}

FragTrap&	FragTrap::operator=(const FragTrap& ref)
{
	this->_name = ref._name;
	this->_attackDamage = ref._attackDamage;
	this->_energyPoints = ref._energyPoints;
	this->_hitPoints = ref._hitPoints;
	std::cout << "[ScavTrap] " << "operator=!!" << std::endl;
	std::cout << "[FragTrap] " << "operator=!!" << std::endl;
	return (*this);
}

FragTrap::FragTrap(std::string name)
{
	_name = name;
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	std::cout << "[FragTrap] " << "create!!" << std::endl;
}

void	FragTrap::highFivesGuys(void)
{
	std::cout<< _name << " request high fives!" << std::endl;
}