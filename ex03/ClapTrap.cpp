#include <iostream>
#include <iomanip>

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
    std::cout << std::setw(15) << "[ClapTrap] " << "create!!" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& ref)
{
    *this=ref;
    std::cout << std::setw(15) << "[ClapTrap] " << "copy!!" << std::endl;
}

ClapTrap::~ClapTrap()
{
    std::cout << std::setw(15) << "[ClapTrap] " << "delete!!" << std::endl;
}

ClapTrap&	ClapTrap::operator=(const ClapTrap& ref)
{
    _name = ref._name;
    _hitPoints = ref._hitPoints;
    _energyPoints = ref._energyPoints;
    _attackDamage = ref._attackDamage;
    std::cout << std::setw(15) << "[ClapTrap] " << "operator=!!" << std::endl;
    return (*this);
}

ClapTrap::ClapTrap(std::string name)
{
    _name = name;
    _attackDamage = 0;
    _hitPoints = 10;
    _energyPoints = 10;
    std::cout << std::setw(15) <<_name<<" is created!"<<std::endl;
}

void    ClapTrap::attack(const std::string& target)
{
    if (_energyPoints == 0)
    {
        std::cout << std::setw(15) <<"Not enough energy..."<<std::endl;
        return ;
    }
    if (_hitPoints <= 0)
    {
        std::cout << std::setw(15) <<_name<<" is broken..."<<std::endl;
        return ;
    }
    std::cout << std::setw(15) <<"ClapTrap "<<_name<<" attacks "<<target<<", causing "<<_attackDamage<<" points of damage!"<<std::endl;
    _energyPoints--;
}

void    ClapTrap::takeDamage(unsigned int amount)
{
    if (_hitPoints <= 0) {
        std::cout << std::setw(15) <<_name << " is broken..."<<std::endl;
        return ;
    }
    _hitPoints -= amount;
    std::cout << std::setw(15) <<_name<<" has taken "<<amount<<" damage"<<std::endl;
    if (_hitPoints <= 0)
        std::cout << std::setw(15) <<_name << " is broken..."<<std::endl;
}

void    ClapTrap::beRepaired(unsigned int amount)
{
    if (_hitPoints <= 0)
    {
        std::cout << std::setw(15) <<_name<<" is broken..."<<std::endl;
        return ;
    }
    if (_energyPoints == 0)
    {
        std::cout << std::setw(15) <<"Not enough energy..."<<std::endl;
        return ; 
    }
    _energyPoints--;
    _hitPoints += amount;
    std::cout << std::setw(15) <<_name<<" repaired "<<amount<<" hitPoints!"<<std::endl;
}