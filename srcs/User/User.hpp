#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <sys/poll.h>
#include <vector>

using namespace std;

enum USER_MODE {
	NEED_NICKNAME = 0,
	NEED_USERREGISTER,
};

#define HOST_NAME "root@127.0.0.1"

class User {
private :
	string 				_name;
	int					_fd;
	USER_MODE			_mode;
	string 				_password;
	vector<string>		_channels;

public:
	User(void);
	User(const string& name, const int& fd);
	const string& getName(void) const;
	void setName(string name);
	USER_MODE getMode(void) const;
	void setMode(USER_MODE mode);
	void joinNewChannel(string channel);
	int	getFD(void) const;
	const vector<string>& getChannel(void) const;
};

#endif
