#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User/User.hpp"
#include <iostream>
#include <map>

using namespace std;

class Channel {
	private :
		string 				_name;
		map<string, User>	_users;
		typedef map<string, User>::const_iterator users_const_iter;

	public :
		User	getUserWithFD(const int& fd) const;
		User	getUserWithName(const string& name) const;
		void	addUser(const string& name, const int& fd);
		void	deleteUser(const string& name);
};

#endif