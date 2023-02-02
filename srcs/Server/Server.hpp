#ifndef SERVER_HPP
#define SERVER_HPP

#include "header.hpp"
#include <sys/_types/_socklen_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/poll.h>
#include <string>

class Server {
typedef void (Server::*pfunc) (int, std::string);
private :
	int								_port;
	std::string						_password;
	int								_socket;
	struct sockaddr_in				_sockaddr;
	struct pollfd					_pollFDs[MAX_FD_SIZE];
	std::map<std::string, pfunc> 	_funcMap;
	std::string		_nicknameList[MAX_FD_SIZE];

	void	_setFunctions(void);
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

	class InitServerException : public std::exception {
	public :
		const char *what(void) const throw();
	};


	// handler.cpp 

	void	handleNICK(int i, std::string);
	void	handleCAP(int i, std::string);
	void	handlePRIVMSG(int i, std::string);
	void	handleLIST(int i, std::string);
	void	handleINVITE(int i, std::string);
	void	handleKICK(int i, std::string);
	void	handlePING(int i, std::string);
	void	handleJOIN(int i, std::string);
	void	handleQUIT(int i, std::string);
	void	handlePART(int i, std::string);
	void	handleNOTICE(int i, std::string);
	void	handlePASS(int i, std::string);
	void	handleUSER(int i, std::string);
};

#endif
