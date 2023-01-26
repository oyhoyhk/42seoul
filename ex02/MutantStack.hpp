#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <iostream>
#include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
private:
	/* data */

public:

	typedef typename std::stack<T>::container_type::iterator iterator;

	iterator begin() {
		return this->c.begin();
	}
	iterator end() {
		return this->c.end();
	}

	MutantStack() {};
	~MutantStack() {};
	MutantStack(const MutantStack &ref) {
		*this = ref;
	}
	MutantStack& operator=(const MutantStack &ref) {
		if (this != &ref) *this = ref;
	}
};

#endif
