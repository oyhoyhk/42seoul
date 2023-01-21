#include "DiamondTrap.hpp"

int main()
{
	DiamondTrap d("Bravo");

	d.attack();

	d.whoAmI();

	std::cout<<d<<std::endl;
	
	d.beRepaired(150);

}