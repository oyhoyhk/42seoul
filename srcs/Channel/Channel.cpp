#include "Channel.hpp"

User	Channel::getUserWithFD(const int& fd) const {
	for(users_const_iter iter = _users.begin(); iter != _users.end(); ++iter) {
		if (iter->second.getFD() == fd)
			return (*iter).second;
	}
	throw std::runtime_error("Can't find user with fd");
}

User	Channel::getUserWithName(const std::string& name) const {
	return _users.at(name);
}

void	Channel::addUser(const std::string& name, const int& fd) {
	_users[name] = User(name, fd);
}

void	Channel::deleteUser(const std::string& name) {
	_users.erase(_users.find(name));
}
