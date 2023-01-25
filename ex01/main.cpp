#include "iter.hpp"

void	powInt(const int &num) {
	std::cout << num * num << "  ";
}

void	powFloat(const float &num) {
	std::cout << num * num << " ";
}

void	powDouble(const double &num) {
	std::cout << num * num << " ";
}

void	decorateString(const std::string &str) {
	std::cout << "*[" << str << "]* ";
}

int main()
{
	int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	float arr2[] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10 };
	double arr3[]= { 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5 , 10.5};

	iter(arr1, 10, powInt); 	
	std::cout<<std::endl<<std::endl;
	iter(arr2, 10, powFloat); 	
	std::cout<<std::endl<<std::endl;
	iter(arr3, 10, powDouble); 	
	std::cout<<std::endl<<std::endl;

	std::string arr4[] = { "Hello", "Good", "Great", "Handsome", "Bravo", "Task" };
	iter(arr4, 5, decorateString);
	std::cout<<std::endl;
	
	system("leaks main | grep 'total'");
}