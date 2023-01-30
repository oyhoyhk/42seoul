#ifndef SERVER_HPP
#define SERVER_HPP

#include "../../includes/header.hpp"
#include <sys/_types/_socklen_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/poll.h>

class Server {
	private :
		struct sockaddr_in	_listenSocket;
		int					_listenFD;
		struct sockaddr_in	_connectSocket;
		socklen_t			_addrSize;
		struct pollfd		_pollFDs[MAX_FD_SIZE];

	public :
		void			setSocket();
		struct pollfd	*getPollFDs();
		void			addPollFD();
		void			sendResponse();
		void			closeListenFD();

		class InitServerException : public std::exception {
			public :
				const char *what(void) const throw();
		};
};

#endif