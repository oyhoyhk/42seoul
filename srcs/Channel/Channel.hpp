#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User/User.hpp"
#include <iostream>
#include <map>

using namespace std;

class User;

enum ChannelMode{
	O = 0,
	P,
	S,
	I,
	T,
	N,
	M,
	L,
	B,
	V,
	K
};

class Channel {
	private :
		string 				_name;
		map<string, User>	_users;
		bool				_mode[11];
		typedef map<string, User>::const_iterator users_const_iter;

	public :
		Channel() {};
		Channel(const string &name);
		User	getUserWithFD(const int& fd) const;
		User	getUserWithName(const string& name) const;
		void	addUser(const string& name, const int& fd);
		void	deleteUser(const string& name);
		const map<string, User> &getUsers() const;

		Channel operator= (const Channel &ref);
}; 

#endif