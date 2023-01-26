#include <climits>
#include <exception>
#include <iostream>

#include "Span.hpp"

const char *Span::SpanException::what(void) const throw(){
	return ("Span funciton error");
}

int	Span::shortestSpan() {
	try {
		if (_list.size() < 2) throw SpanException();
		std::sort(_list.begin(), _list.end());
		int min = INT_MAX;
		for (unsigned int i=1; i < _list.size() ;i++) {
			if (_list[i] - _list[i - 1] < min)
				min = _list[i] - _list[i - 1];
		}
		return min;
	} catch (std::exception &e) {
		std::cerr << e.what() << "  ";
		return -1;
	}
}

int	Span::longestSpan() {
	try {
		if (_list.size() < 2) throw SpanException();
			std::sort(_list.begin(), _list.end());
		return _list.back() - _list[0];
	} catch (std::exception &e) {
		std::cerr << e.what() << "  ";
		return -1;
	}
}

void Span::addRange() {
	int i = 0;
	while (_list.size() < _max)
		_list.push_back(++i);

}

void	Span::addNumber(int num) {
	try {
		if (_list.size() == _max) throw SpanException();
		_list.push_back(num);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

Span::Span() : _max(0) {
}

Span::Span(const Span& ref)  {
	this->_list=ref._list;
}

Span::~Span() {}

Span&	Span::operator=(const Span& ref) {
	this->_list = ref._list;
	return (*this);
}

void	Span::print() {
	for (unsigned int i=0; i<_list.size();i++) {
		std::cout << _list[i] << "  ";
	}
	std::cout<<std::endl;
}

Span::Span(unsigned int n) : _max(n) {}
