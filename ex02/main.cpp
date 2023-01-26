#include "MutantStack.hpp"
#include <iterator>

int main()
{
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << "mstack.top : " << mstack.top() << std::endl;
	mstack.pop();
	std::cout << "mstack.top : " << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
	std::cout << *it << std::endl;
	++it;
	}
	std::stack<int> s(mstack);

	std::cout<<std::endl;
	MutantStack<std::string> test;
	test.push("test");
	test.push("Good");

	std::cout<<"test.top : "<<test.top()<<std::endl;
	std::cout<<"test.size : "<<test.size()<<std::endl;

	test.push("abcdefg");
	test.push("123456");
	test.push("zmncvifjw");
	test.push("babo");
	test.push("cong");

	MutantStack<std::string>::iterator it2 = test.begin();
	MutantStack<std::string>::iterator it2e = test.end();
	++it2;
	--it2e;
	while(it2 != it2e)
	{
		std::cout << *it2 << std::endl;
		++it2;
	}
	return 0;
}