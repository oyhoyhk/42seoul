#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User/User.hpp"
#include <iostream>
#include <map>

class Channel {
	private :
		std::string 				_name;
		std::map<std::string, User>	_users;
		typedef std::map<std::string, User>::const_iterator users_const_iter;

	public :
		User	getUserWithFD(const int& fd) const;
		User	getUserWithName(const std::string& name) const;
		void	addUser(const std::string& name, const int& fd);
		void	deleteUser(const std::string& name);
};

#endif