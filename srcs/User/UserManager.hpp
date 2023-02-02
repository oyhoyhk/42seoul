#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include "User/User.hpp"
#include "header.hpp"

class UserManager {
private:
	typedef std::map<std::string, User>::const_iterator users_const_iter;
	std::map<std::string, User>		_users;
public:
	User	getUserWithFD(const int& fd) const;
	User	getUserWithName(const std::string& name) const;
	void	addUser(const std::string& name, const int& fd);
	void	deleteUser(const std::string& name);
};

#endif
