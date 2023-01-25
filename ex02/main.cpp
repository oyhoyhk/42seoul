#include "Classes.hpp"
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>

Base	*generate(void);
void	identify(Base *p);
void	identify(Base &p);

int main()
{
	srand(std::time(NULL));
	identify(generate());
	identify(generate());
	identify(generate());


	std::cout<<std::endl;
	Base *a = generate();
	Base *b = generate();
	Base *c = generate();

	identify(*a);
	identify(*b);
	identify(*c);

	system("leaks main | grep 'total'");
}

Base	*generate(void) {
	int val = std::rand() % 3;
	switch (val) {
		case 0 :
			return new A();
		case 1 :
			return new B();
		case 2 :
			return new C();
	}
	return NULL;
}

void	identify(Base *p) {
	if (dynamic_cast<A *>(p)) {
		std::cout << "Base is A" << std::endl;
		delete p;
	} else if (dynamic_cast<B *>(p)) {
		std::cout << "Base is B" << std::endl;
		delete p;
	} else if (dynamic_cast<C *>(p)) {
		std::cout << "Base is C" << std::endl;
		delete p;
	} else {
		std::cout <<"Type Error!" << std::endl;
	}
}

void	identify(Base &p) {
	try {
		A &a = dynamic_cast<A&>(p);
		std::cout << "Base is A" << std::endl;
		static_cast<void>(a);
		return ;
	}
	catch (std::exception &e){}
	try {
		B &b = dynamic_cast<B&>(p);
		std::cout << "Base is B" << std::endl;
		static_cast<void>(b);
		return ;
	}
	catch (std::exception &e){}
	try {
		C &c = dynamic_cast<C&>(p);
		std::cout << "Base is C" << std::endl;
		static_cast<void>(c);
		return ;
	}
	catch (std::exception &e){}
}