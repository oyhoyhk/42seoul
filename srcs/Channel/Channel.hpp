#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "header.hpp"
#include "User/User.hpp"

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
	typedef map<string, User*>::const_iterator users_const_iter;
	typedef map<string, User*>::iterator users_iter;

	string 				_name;
	map<string, User*>	_users;
	unsigned int		_mode_bit;

	Channel operator= (const Channel& ref);
	Channel (const Channel& ref);

public :
	Channel(void);
	Channel(const string &name);

	const string& getName(void) const;

	bool	hasUser(const User* user) const;
	void	addUser(User* user);
	void	deleteUser(const User* user);

	void	setMode(const ChannelMode& mode);
	void	unsetMode(const ChannelMode& mode);
	bool	isSetMode(const ChannelMode& mode) const;
}; 

#endif