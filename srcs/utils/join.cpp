#include <iostream>
#include <vector>
#include "Utils.hpp"

std::string join(std::vector<std::string> vec) {
	std::string ret = ":";
	std::string delimiter = " ";

	for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++) {
		ret += *it;
		if (it != vec.end() - 1)
			ret += delimiter;
	}
	return ret;
}