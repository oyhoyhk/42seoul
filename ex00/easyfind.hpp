#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

template <typename C>
typename C::iterator easyfind(C* container, int value) {
	typename C::iterator iter = std::find(std::begin(*container), std::end(*container), value);
	if (iter == std::end(*container))
		throw std::runtime_error("Target does not exist...");
	return iter;
}


#endif