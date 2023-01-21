#include "FragTrap.hpp"

int main()
{
	FragTrap a("Hello");
	FragTrap b("World");

	a.attack("Test");
	b.attack("Great");

	a.beRepaired(150);
	a.takeDamage(80);
	a.beRepaired(100);
	
	a.highFivesGuys();
	b.highFivesGuys();
	return 0;
}