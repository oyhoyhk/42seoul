#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <sys/poll.h>
#include <vector>
#include "Channel/Channel.hpp"
#include <map>

using namespace std;

enum USER_STATUS {
	NEED_NICKNAME = 0,
	NEED_USERREGISTER,
};

enum UserMode {
	I = 0,
	S,
	W,
	O
};

#define HOST_NAME "root@127.0.0.1"

class Channel;

class User {
private :
	typedef map<string, Channel*>::const_iterator channels_const_iter;
	typedef map<string, Channel*>::iterator channels_iter;
	string 					_name;
	int						_fd;
	USER_STATUS				_status;
	unsigned int			_mode_bit;
	string 					_password;
	map<string, Channel*>	_channels;

	User operator= (const User& ref);
	User (const User& ref);

public:
	User(void);
	User(const string& name, const int& fd);

	const string& getName(void) const;
	int	getFD(void) const;
	const string& getPassword(void) const;

	bool	hasChannel(const Channel* channel) const;
	void	joinChannel(Channel* channel);
	void	partChannel(const Channel* channel);

	void	setMode(const UserMode& mode);
	void	unsetMode(const UserMode& mode);
	bool	isSetMode(const UserMode& mode) const;
};

#endif
