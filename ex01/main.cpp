#include <iostream>

struct Data {
	std::string name;
};

uintptr_t	serialize(Data *ptr) {
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data*	deserialize(uintptr_t raw) {
	return reinterpret_cast<Data *>(raw);
}

int main() {
	Data prev;

	unsigned int val = serialize(&prev);
	std::cout<<"serialize : " << std::hex << val << std::endl;
	std::cout<<"deserialize : " << deserialize(val) << std::endl;

	return 0;
}