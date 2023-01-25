#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template <typename T>
void iter(T* arr, std::size_t len, void (*f)(const T&)) {
	for (std::size_t i = 0; i < len; i++)
		f(arr[i]);
}

#endif