#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <sys/poll.h>

class User {
	private :
		std::string 	_nickname;
		struct pollfd	_pollFD;
};

#endif