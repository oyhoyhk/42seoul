#include "User/User.hpp"

User::User(void) {
	this->_fd = -1;
}

User::User(const std::string& name, const int& fd) {
	this->_name = name;
	this->_fd = fd;
}

const std::string& User::getName(void) const {
	return _name;
}

int	User::getFD(void) const {
	return _fd;
}
