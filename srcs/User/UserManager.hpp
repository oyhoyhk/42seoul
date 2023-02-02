#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include "User/User.hpp"
#include "header.hpp"

class UserManager {
private:
	typedef map<string, User>::const_iterator users_const_iter;
	map<string, User>		_users;
public:
	User	getUserWithFD(const int& fd) const;
	User	getUserWithName(const string& name) const;
	void	addUser(const string& name, const int& fd);
	void	deleteUser(const string& name);
	const map<string, User>& getUsers(void) const;
};

#endif
