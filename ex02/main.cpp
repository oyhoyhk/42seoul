#include "Array.hpp"
#include <iostream>

template <typename T>
void	test(Array<T> list, int len) {
	for (int i = 0; i < len; i++) 
		std::cout << list[i] + list[i] << "  ";
	std::cout<<std::endl<<std::endl;
}

int main() {
	Array<int> intArr(10);

	for(int i=0;i<10;i++) 
		*const_cast<int *>(&intArr[i]) = i * 10 +3;
	for(int i=0;i<10;i++)
		std::cout << intArr[i] << " ";
	std::cout<<std::endl;



	test(intArr, 10);

	Array<float> floatArr(10);
	for(int i=0;i<10;i++) 
		*const_cast<float *>(&floatArr[i]) = i *3 + 0.3;

	test(floatArr, 10);

	Array<double> doubleArr(10);
	for(int i=0;i<10;i++) 
		*const_cast<double *>(&doubleArr[i]) = i * 2 + 0.47;

	Array<std::string> stringArr(10);
	for(int i=0;i<10;i++) 
		*const_cast<std::string *>(&stringArr[i]) = "Test_" + std::to_string(i);

	test(stringArr, 10);
	std::cout<<std::endl;

	try {
		std::cout<<intArr[10]<<std::endl;
	} catch (std::exception &e) {
		std::cerr<<e.what()<<std::endl;
	}
	return 0;
}