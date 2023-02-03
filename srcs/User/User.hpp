#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <sys/poll.h>
#include <vector>
#include "Channel/Channel.hpp"
#include <map>

using namespace std;

enum USER_MODE {
	NEED_NICKNAME = 0,
	NEED_USERREGISTER,
};

#define HOST_NAME "root@127.0.0.1"

class Channel;

class User {
private :
	string 					_name;
	int						_fd;
	USER_MODE				_mode;
	string 					_password;
	map<string, Channel>	_channels;

public:
	User(void);
	User(const string& name, const int& fd);
	const string& getName(void) const;
	void setName(string name);
	USER_MODE getMode(void) const;
	void setMode(USER_MODE mode);
	void joinChannel(const string &channel);
	void partChannel(void);
	int	getFD(void) const;
	const map<string, Channel>& getChannels(void) const;
};

#endif
