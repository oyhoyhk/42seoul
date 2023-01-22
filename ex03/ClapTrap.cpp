#include <iostream>


#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
    std::cout << "[ClapTrap] " << "create!!" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
{
    _name = name;
    _attackDamage = 0;
    _hitPoints = 10;
    _energyPoints = 10;
    std::cout <<"[ClapTrap] " << _name<<" is created!"<<std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& ref)
{
    *this=ref;
    std::cout << "[ClapTrap] " << "copy!!" << std::endl;
}

ClapTrap::~ClapTrap()
{
    std::cout << "[ClapTrap] " << "delete!!" << std::endl;
}

ClapTrap&	ClapTrap::operator=(const ClapTrap& ref)
{
    _name = ref._name;
    _hitPoints = ref._hitPoints;
    _energyPoints = ref._energyPoints;
    _attackDamage = ref._attackDamage;
    std::cout << "[ClapTrap] " << "operator=!!" << std::endl;
    return (*this);
}


void    ClapTrap::attack(const std::string& target)
{
    if (_energyPoints == 0)
    {
        std::cout <<"Not enough energy..."<<std::endl;
        return ;
    }
    if (_hitPoints <= 0)
    {
        std::cout <<_name<<" is broken..."<<std::endl;
        return ;
    }
    std::cout <<"ClapTrap "<<_name<<" attacks "<<target<<", causing "<<_attackDamage<<" points of damage!"<<std::endl;
    _energyPoints--;
}

void    ClapTrap::takeDamage(unsigned int amount)
{
    if (_hitPoints <= 0) {
        std::cout <<_name << " is broken..."<<std::endl;
        return ;
    }
    _hitPoints -= amount;
    std::cout <<_name<<" has taken "<<amount<<" damage"<<std::endl;
    if (_hitPoints <= 0)
        std::cout <<_name << " is broken..."<<std::endl;
}

void    ClapTrap::beRepaired(unsigned int amount)
{
    if (_hitPoints <= 0)
    {
        std::cout <<_name<<" is broken..."<<std::endl;
        return ;
    }
    if (_energyPoints == 0)
    {
        std::cout <<"Not enough energy..."<<std::endl;
        return ; 
    }
    _energyPoints--;
    _hitPoints += amount;
    std::cout <<_name<<" repaired "<<amount<<" hitPoints!"<<std::endl;
}

const std::string &ClapTrap::getName(void) const
{
    return _name;
}

const int &ClapTrap::getHitPoints(void) const
{
    return _hitPoints;
}

const int &ClapTrap::getEnergyPoints(void) const
{
    return _energyPoints;
}

const int &ClapTrap::getAttackDamage(void) const
{
    return _attackDamage;
}

std::ostream    &operator<<(std::ostream &out, const ClapTrap &ref)
{
    out << "[ClapTrap] name : " << ref.getName();
    out << " HP : " << ref.getHitPoints();
    out << " MP : " << ref.getEnergyPoints();
    out << " AD : " << ref.getAttackDamage();

    return out;
}