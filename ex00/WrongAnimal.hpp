#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <iostream>

class WrongAnimal
{
protected:
	std::string _type;
public:
	WrongAnimal();
	WrongAnimal(const WrongAnimal& ref);
	~WrongAnimal();

	WrongAnimal&	operator=(const WrongAnimal& ref);
	void	makeSound(void) const;
};

#endif
