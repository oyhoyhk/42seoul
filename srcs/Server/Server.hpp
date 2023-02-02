#ifndef SERVER_HPP
#define SERVER_HPP

#include "Server/Command.hpp"
#include "header.hpp"
#include "User/User.hpp"
#include "User/UserManager.hpp"
#include "Channel/Channel.hpp"
#include <sys/socket.h>
#include <sys/poll.h>
#include <string>

class Command;

class Server {
typedef void (Server::*pfunc) (int, std::string);
private :
	int								_port;
	std::string						_password;
	int								_socket;
	struct pollfd					_pollFDs[MAX_FD_SIZE];
	UserManager						_userManager;
	std::map<std::string, Channel>	_channels;
	Command*						_command;

	void	_acceptConnections(void);
	void	_sendResponse(void);


public :
	Server(const std::string& port, const std::string& password);
	~Server();

	/*
	** @brief server 소켓 liten까지 실행
	** @throw 도중에 실패하면 _socket close하고 InitServerException 던짐
	*/
	void 	prepare(void);

	/*
	** @brief server poll 실행 무한 반복
	*/
	void	start(void);

	UserManager& getUserManager(void);


	class InitServerException : public std::exception {
	public :
		const char *what(void) const throw();
	};
};

#endif
