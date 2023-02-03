#include "header.hpp"
#include "UserManager.hpp"

User	UserManager::getUserWithFD(const int& fd) const {
	for(users_const_iter iter = _users.begin(); iter != _users.end(); ++iter) {
		if (iter->second.getFD() == fd)
			return (*iter).second;
	}
	throw runtime_error("Can't find user with fd");
}

User	UserManager::getUserWithName(const string& name) const {
	return _users.at(name);
}

void	UserManager::addUser(const string& name, const int& fd) {
	_users[name] = User(name, fd);
}

void	UserManager::deleteUser(const string& name) {
	_users.erase(_users.find(name));
}

const map<string, User>& UserManager::getUsers(void) const {
	return _users;
}
