#include "ScavTrap.hpp"

int main()
{
	ScavTrap a("Hello");
	ScavTrap b("World");

	a.attack("Test");
	b.attack("Great");

	a.guardGate();
	b.guardGate();

	a.beRepaired(100);
	return 0;
}