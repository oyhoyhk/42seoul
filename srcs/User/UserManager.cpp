#include "header.hpp"
#include "UserManager.hpp"

UserManager::~UserManager() {
	for (users_iter iter = _users.begin(); iter != _users.end(); ++iter)
		delete iter->second;
}

User*	UserManager::getUserWithFD(const int& fd) const {
	for(users_const_iter iter = _users.begin(); iter != _users.end(); ++iter) {
		if (iter->second->getFD() == fd)
			return iter->second;
	}
	return NULL;
}

User*	UserManager::getUserWithName(const string& name) const {
	users_const_iter temp = _users.find(name);
	if (temp == _users.end()) return NULL;
	return temp->second;
}

bool	UserManager::addUser(const string& name, const int& fd) {
	if (getUserWithName(name)) return false;
	_users[name] = new User(name, fd);
	return true;
}

void	UserManager::deleteUser(const string& name) {
	users_iter temp = _users.find(name);
	if (temp == _users.end()) return;
	delete temp->second;
	_users.erase(temp);
}

void	UserManager::deleteUser(User* user) {
	deleteUser(user->getName());
}