#include "Channel.hpp"

Channel Channel::operator= (const Channel& ref) { }
Channel::Channel (const Channel& ref) { }

Channel::Channel(void):_mode_bit(0) { }

Channel::Channel(const string &name) : _name(name), _mode_bit(0) { }

bool	Channel::hasUser(const User* user) const {
	users_const_iter iter = _users.find(user->getName());
	if (iter == _users.end()) return false;
	return true;
}

const string& Channel::getName(void) const {
	return _name;
}

void	Channel::addUser(User* user) {
	if (hasUser(user)) return;
	_users[user->getName()] = user;
}

void	Channel::deleteUser(const string& user_name) {
	users_iter iter = _users.find(user_name);
	if (iter == _users.end()) return;
	_users.erase(iter);
}

void	Channel::deleteUser(const User* user) {
	deleteUser(user->getName());
}

void	Channel::setMode(const ChannelMode& mode) {
	_mode_bit &=  1 << mode;
}

void	Channel::unsetMode(const ChannelMode& mode) {
	_mode_bit &= ~(1 << mode);
}

bool	Channel::isSetMode(const ChannelMode& mode) const {
	return _mode_bit & (1 << mode);
}

vector<User*> Channel::getUsers(void) const {
	vector<User*> ret;
	for(users_const_iter iter = _users.begin(); iter != _users.end(); ++iter)
		ret.push_back(iter->second);
	return ret;
}