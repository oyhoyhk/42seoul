#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
	const int 	num = 6;
	Animal *arr[num];

	for(int i=0;i<num;i++) {
		std::cout << i + 1 << "th Animal is Created!" << std::endl;
		if (i % 2 == 0)
			arr[i] = new Cat();
		else
		 	arr[i] = new Dog();
		arr[i]->makeSound();
		std::cout<<std::endl;
	}

	Dog a;
	Dog b;

	a = b;

	for(int i=0;i<num;i++) {
		std::cout << i + 1<< "th Animal will be destroyed" << std::endl;
		delete arr[i];
	}

	system("leaks main | grep 'total leaked bytes'");
}