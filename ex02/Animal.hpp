#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>

class Animal
{
protected:
	std::string _type;
public:
	Animal();
	Animal(const Animal& ref);
	virtual ~Animal();

	Animal&	operator=(const Animal& ref);

	virtual void	makeSound(void) const = 0;
	std::string	getType(void) const;

};

#endif
