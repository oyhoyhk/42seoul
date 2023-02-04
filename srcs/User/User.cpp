#include "User/User.hpp"

User::User(void): _name("*"), _fd(-1), _mode_bit(0) {}

User::User(const string& name, const int& fd): _name(name), _fd(fd), _mode_bit(0) { }

const string& User::getName(void) const { return _name; }

int	User::getFD(void) const { return _fd; }

const string& User::getPassword(void) const { return _password; }


bool User::hasChannel(const Channel* channel) const {
	channels_const_iter iter = _channels.find(channel->getName());
	return iter != _channels.end();
}

void User::joinChannel(Channel* channel) {
	if (hasChannel(channel)) return ;
	_channels[channel->getName()] = channel;
}

void User::partChannel(const Channel* channel) {
	channels_const_iter iter = _channels.find(channel->getName());
	if (iter == _channels.end()) return;
	_channels.erase(iter);
}

void	User::setMode(const UserMode& mode) {
	_mode_bit &=  1 << mode;
}

void	User::unsetMode(const UserMode& mode) {
	_mode_bit &= ~(1 << mode);
}

bool	User::isSetMode(const UserMode& mode) const {
	return _mode_bit & (1 << mode);
}