#ifndef SPAN_HPP
# define SPAN_HPP

#include <exception>
#include <vector>
class Span
{
private:
	std::vector<int>	_list;
	unsigned int		_max;
public:
	void	addNumber(int num);
	void	addRange();
	int		shortestSpan();
	int		longestSpan();
	void	sort();
	void	print();

	Span();
	Span(unsigned int n);
	Span(const Span& ref);
	~Span();
	Span&	operator=(const Span& ref);

	class SpanException : public std::exception {
		public:
			const char *what() const throw();
	};
	
};

#endif
