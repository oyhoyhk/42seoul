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
	//(void channel);

	map<string, Channel>& userChannel = getChannel();
	
	// 유저가 가입한 채널에 속하지 않으면
	if (userChannel.find(channel) == userChannel.end()) {
		userChannel[channel] = Channel(channel);
	} else {
		// 유저가 가입한 채널에 속할 때
	}
	//map<string, Channel>::iterator iter;
	//iter = find(this->_channels.begin(), this->_channels.end(), channel);
	////if (iter != this->_channels.end())
	//	//this->_channels.erase(iter);
	
}

void User::partChannel(void) {
	//
}

void User::setName(string name) {
	this->_name = name;
}

const map<string, Channel>& User::getChannel(void) const {
	return this->_channels;
}

USER_STATUS User::getStatus(void) const {
	return this->_status;
}

void User::setStatus(USER_STATUS status) {
	this->_status = status;
}

int *User::getMode(void) {
	return this->_mode;
}

void User::setMode(int mode) {
	this->_mode[mode] = 1;
}