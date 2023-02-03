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

#define SERVER_PREFIX "irc.local"

class Server {
typedef void (Server::*pfunc) (int, string);
private :
	int								_port;
	string							_password;
	int								_socket;
	struct pollfd					_pollFDs[MAX_FD_SIZE];
	UserManager						_userManager;
	map<string, Channel>			_channels;
	Command*						_command;

	void	_acceptConnections(void);
	void	_sendResponse(void);
	void	_joinChannel(const string &channel, const string &name, const int &fd);
	void	_partChannel(const string &channel, const string &name);

public :
	Server(const string& port, const string& password);
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


	class InitServerException : public exception {
	public :
		const char *what(void) const throw();
	};
};

#endif
