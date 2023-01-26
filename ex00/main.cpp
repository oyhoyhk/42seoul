#include "easyfind.hpp"
#include <iterator>
#include <vector>
#include <deque>
#include <list>
#include <iostream>

int main() {
	std::vector<int> v1;
	std::deque<int> d1;
	std::list<int> l1;

	for (int i=0;i<10;i++) {
		v1.push_back(i);
		d1.push_back(i);
		l1.push_back(i);
	}
	int val = 3;
	std::cout << " vector : " << std::distance(v1.begin(), easyfind(&v1, val))<< std::endl;
	std::cout << " deque : " << std::distance(d1.begin(), easyfind(&d1, val))<< std::endl;
	std::cout << " list : " << std::distance(l1.begin(), easyfind(&l1, val))<< std::endl;

	val = 150;
	try {
		std::cout << " vector : " << std::distance(v1.begin(), easyfind(&v1, val))<< std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		std::cout << " deque : " << std::distance(d1.begin(), easyfind(&d1, val))<< std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		std::cout << " list : " << std::distance(l1.begin(), easyfind(&l1, val))<< std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}