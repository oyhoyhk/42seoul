#include "ClapTrap.hpp"

int main()
{
    ClapTrap    clapTrap("TrapA");
    ClapTrap    clapTrap2("TrapB");

    clapTrap.attack("clapTrap2");
    clapTrap2.attack("clapTrap");
    clapTrap2.takeDamage(5);
    clapTrap2.beRepaired(4);
    clapTrap2.takeDamage(10);
    clapTrap2.beRepaired(10);
    return (0);

}