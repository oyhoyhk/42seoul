#include <iostream>

#include "Brain.hpp"

Brain::Brain()
{
	for (int i = 0; i < 100; i++)
		_ideas[i] = "brain" + std::to_string(i);
	std::cout << "[Brain] " << "create!!" << std::endl;
}

Brain::Brain(const Brain& ref)
{
	*this=ref;
	std::cout << "[Brain] " << "copy!!" << std::endl;
}

Brain::~Brain()
{
	std::cout << "[Brain] " << "delete!!" << std::endl;
}

Brain&	Brain::operator=(const Brain& ref)
{
	for (int i=0;i<100;i++)
		this->_ideas[i] = ref._ideas[i];
	std::cout << "[Brain] " << "operator=!!" << std::endl;
	return (*this);
}
