#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
    ScavTrap a("Yooh");
    ScavTrap b("Cabi");

    FragTrap c("Frag");
    FragTrap d("Good");

    a.attack("Alpha");
    b.attack("Beta");

    a.takeDamage(30);
    b.takeDamage(150);
    a.beRepaired(50);
    b.beRepaired(100);

    a.guardGate();
    b.guardGate();

    c.highFivesGuys();
    c.attack("Bad");
    d.beRepaired(150);
    c.takeDamage(100);
    return 0;
}