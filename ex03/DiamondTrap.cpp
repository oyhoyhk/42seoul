#include <iostream>


#include "ClapTrap.hpp"
#include "DiamondTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

DiamondTrap::DiamondTrap()
{
	_name = "John";
	_hitPoints = FragTrap::_hitPoints;
	_energyPoints = ScavTrap::_energyPoints;
	_attackDamage = FragTrap::_attackDamage;
	std::cout << "[DiamondTrap] " << _name << " create!!" << std::endl;
}
DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name")
{
	_name = name;
	std::cout << "[DiamondTrap] " << _name << " create!!" << std::endl;
}


DiamondTrap::DiamondTrap(const DiamondTrap& ref)
{
	*this=ref;
	std::cout << "[DiamondTrap] " << "copy!!" << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "[DiamondTrap] " << "delete!!" << std::endl;
}

DiamondTrap&	DiamondTrap::operator=(const DiamondTrap& ref)
{
	this->_name = ref._name;
	this->_attackDamage  = ref._attackDamage;
	this->_energyPoints = ref._energyPoints;
	this->_hitPoints = ref._hitPoints;
	std::cout << "[DiamondTrap] " << "operator=!!" << std::endl;
	return (*this);
}

void	DiamondTrap::attack(void)
{
	ScavTrap::attack();	
}

void	DiamondTrap::whoAmI(void)
{
	std::cout << "[DiamondTrap] name : " << _name << " // [ClapTrap] name : " << ClapTrap::_name << std::endl;
}

const   std::string &DiamondTrap::getName(void) const
{
	return _name;
}
const   int &DiamondTrap::getHitPoints(void) const
{
	return _hitPoints;
}
const   int &DiamondTrap::getEnergyPoints(void) const
{
	return _energyPoints;
}
const   int &DiamondTrap::getAttackDamage(void) const
{
	return _attackDamage;
}

std::ostream    &operator<<(std::ostream &out, const DiamondTrap &ref)
{
    out << "[DiamondTrap] name : " << ref.getName();
    out << " HP : " << ref.getHitPoints();
    out << " MP : " << ref.getEnergyPoints();
    out << " AD : " << ref.getAttackDamage();

    return out;
}