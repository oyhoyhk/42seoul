#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
	Dog *dog = new Dog();
	Cat *cat = new Cat();

	//Animal *animal = new Animal();

	dog->makeSound();
	cat->makeSound();
	//animal->makeSound();

	std::cout<<std::endl;

	delete dog;
	std::cout<<std::endl;
	delete cat;
	std::cout<<std::endl;
	//delete animal;

	system("leaks main");
}