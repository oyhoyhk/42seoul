#include "Span.hpp"
#include <iostream>

int main()
{
	Span sp = Span(5);
	sp.addNumber(6);


	sp.print();
	std::cout << "shortestSpan : " << sp.shortestSpan() << std::endl;
	std::cout << "longestSpan : " << sp.longestSpan() << std::endl << std::endl;

	sp.addNumber(3);
	sp.addNumber(17);

	sp.print();
	std::cout << "shortestSpan : " << sp.shortestSpan() << std::endl;
	std::cout << "longestSpan : " << sp.longestSpan() << std::endl << std::endl;

	sp.addNumber(9);
	sp.addNumber(11);

	sp.print();
	std::cout << "shortestSpan : " << sp.shortestSpan() << std::endl;
	std::cout << "longestSpan : " << sp.longestSpan() << std::endl << std::endl;;

	sp.addNumber(150);

	std::cout<<std::endl;

	Span test(10000);
	test.addRange();
	test.print();
	std::cout << "shortestSpan : " << test.shortestSpan() << std::endl;
	std::cout << "longestSpan : " << test.longestSpan() << std::endl << std::endl;;

	return 0;
}