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
    *this=ref;
    std::cout << std::setw(15) << "[ClapTrap] " << "operator=!!" << std::endl;
    return (*this);
}

void    ClapTrap::attack(const std::string& target)
{
    if (_energyPoints == 0)
    {
        std::cout<<"Not enough energy..."<<std::endl;
        return ;
    }
    std::cout<<"ClapTrap "<<_name<<" attacks "<<target<<", causing "<<_attackDamage<<" points of damage!"<<std::endl;
    _energyPoints--;
}

void    ClapTrap::takeDamage(unsigned int amount)
{
    if (_hitPoints <= amount)
    {
        std::cout<<_name<<" is broken..."<std::endl;
        return ;
    }
    _hitPoints -= amount;
    std::cout<<_name<<" has taken "<<amount<<" damage"<<std::endl;
}

void    ClapTrap::beRepaired(unsigned int amount)
{
    if (_energyPoints == 0)
    {
        std::cout<<"Not enough energy..."<<std::endl;
        return ; 
    }
    _energyPoints--;
    std::cout<<_name<<" repaired "<<amount<<" hitPoints!"<<std::endl;
}