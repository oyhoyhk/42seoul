#include "Channel.hpp"

Channel::Channel(const string &name) : _name(name) {}

User	Channel::getUserWithFD(const int& fd) const {
	for(users_const_iter iter = _users.begin(); iter != _users.end(); ++iter) {
		if (iter->second.getFD() == fd)
			return (*iter).second;
	}
	throw runtime_error("Can't find user with fd");
}

User	Channel::getUserWithName(const string& name) const {
	return _users.at(name);
}

void	Channel::addUser(const string& name, const int& fd) {
	_users[name] = User(name, fd);
}

void	Channel::deleteUser(const string& name) {
	_users.erase(_users.find(name));
}

Channel Channel::operator= (const Channel &ref) {
	return ref;
}

const map<string, User> &Channel::getUsers() const {
	return _users;
}