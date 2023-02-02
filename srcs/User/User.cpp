#include "User/User.hpp"

User::User(void) {
	this->_fd = -1;
	this->_name = "*";
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

void User::joinNewChannel(std::string channel) {
	this->_channels.push_back(channel);
}

void User::setName(std::string name) {
	this->_name = name;
}

const std::vector<std::string>& User::getChannel(void) const {
	return this->_channels;
}

USER_MODE User::getMode(void) const {
	return this->_mode;
}

void User::setMode(USER_MODE mode) {
	this->_mode = mode;
}