#include <iostream>
#include <iomanip>

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
{
	std::cout << std::setw(15) << "[DiamondTrap] " << "create!!" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[DiamondTrap] " << "copy!!" << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << std::setw(15) << "[DiamondTrap] " << "delete!!" << std::endl;
}

DiamondTrap&	DiamondTrap::operator=(const DiamondTrap& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[DiamondTrap] " << "operator=!!" << std::endl;
	return (*this);
}
