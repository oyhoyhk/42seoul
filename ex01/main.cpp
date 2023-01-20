#include "ScavTrap.hpp"

int main()
{
    ScavTrap a("Yooh");
    ScavTrap b("Cabi");

    a.attack("Alpha");
    b.attack("Beta");

    a.takeDamage(30);
    b.takeDamage(150);
    a.beRepaired(50);
    b.beRepaired(100);

    a.guardGate();
    b.guardGate();
}