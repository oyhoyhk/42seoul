#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <sys/poll.h>

class User {
private :
	std::string 	_name;
	int				_fd;

public:
	User(void);
	User(const std::string& name, const int& fd);
	const std::string& getName(void) const;
	int	getFD(void) const;
};

#endif
