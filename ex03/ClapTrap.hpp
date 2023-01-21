#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <iostream>

class ClapTrap
{
protected:
    std::string _name;
    int         _hitPoints;
    int         _energyPoints;
    int         _attackDamage;
public:
    ClapTrap();
    ClapTrap(std::string name);
    ClapTrap(const ClapTrap& ref);
    ~ClapTrap();

    ClapTrap&	operator=(const ClapTrap& ref);

    void    attack(const std::string& target);
    void    takeDamage(unsigned int amount);
    void    beRepaired(unsigned int amount);

    const   std::string &getName(void) const;
    const   int &getHitPoints(void) const;
    const   int &getEnergyPoints(void) const;
    const   int &getAttackDamage(void) const;
};

std::ostream    &operator<<(std::ostream &out, const ClapTrap &ref);

#endif
