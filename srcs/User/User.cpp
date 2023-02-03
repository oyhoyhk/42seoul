#include "User/User.hpp"

User::User(void) {
	this->_fd = -1;
	this->_name = "*";
}

User::User(const string& name, const int& fd) {
	this->_name = name;
	this->_fd = fd;
}

const string& User::getName(void) const {
	return _name;
}

int	User::getFD(void) const {
	return _fd;
}

void User::joinChannel(const string &channel) {
	vector<string>::iterator iter;
	iter = find(this->_channels.begin(), this->_channels.end(), channel);
	if (iter != this->_channels.end())
		this->_channels.erase(iter);
	_channels.push_back(channel);
}

void User::partChannel(void) {
	_channels.pop_back();
}

void User::setName(string name) {
	this->_name = name;
}

const vector<string>& User::getChannel(void) const {
	return this->_channels;
}

USER_MODE User::getMode(void) const {
	return this->_mode;
}

void User::setMode(USER_MODE mode) {
	this->_mode = mode;
}