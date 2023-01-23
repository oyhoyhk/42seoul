#include "Bureaucrat.hpp"

int main()
{
	Bureaucrat a("Hello", 166);
	Bureaucrat b("World", -1);
	Bureaucrat c("Nice", 125);
	Bureaucrat d("Great", 70);

	a.decrement();
	b.decrement();
	c.decrement();
	c.decrement();
	c.decrement();
	c.decrement();
	c.decrement();
	d.increment();
	d.increment();
	d.increment();
	d.increment();
	d.increment();
	d.increment();
}