#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <sys/poll.h>
#include <vector>

enum USER_MODE {
	NEED_NICKNAME = 0,
	NEED_USERREGISTER,
};

#define HOST_NAME "root@127.0.0.1"

class User {
private :
	std::string 				_name;
	int							_fd;
	std::vector<std::string>	_channels;
	USER_MODE					_mode;
	std::string 				_password;

public:
	User(void);
	User(const std::string& name, const int& fd);
	const std::string& getName(void) const;
	void setName(std::string name);
	USER_MODE getMode(void) const;
	void setMode(USER_MODE mode);
	void joinNewChannel(std::string channel);
	int	getFD(void) const;
	const std::vector<std::string>& getChannel(void) const;
};

#endif
