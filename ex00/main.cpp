#include "Input.hpp"
#include <exception>
#include <ios>
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr<<"Argument Error!"<<std::endl;
		return 1;
	}
	char *endPtr;
	double result = strtod(argv[1], &endPtr);

	Input input(result);
	if (argv[1] == endPtr) input.setIsNumber(false);
	if (result != result) input.setIsNaN();
	if (result != 0 && result * 2 == result) input.setIsInf();

	std::cout << input;
}