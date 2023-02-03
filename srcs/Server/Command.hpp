#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "header.hpp"
#include "Server/Server.hpp"
#include "Response.hpp"
#include "poll.h"

#define RES_SELF 0
#define RES_OTHER 1

class Server;

class Command {
private:
	typedef void(Command::*_pfunc)(Server& server, int, const string&);
	typedef map<string, _pfunc>::iterator iter_cmd;

	map<string, _pfunc>	_cmds;

	void	_handleNICK(Server& server, int fd, const string&);
	void	_handleCAP(Server& server, int fd, const string&);
	void	_handlePRIVMSG(Server& server, int fd, const string&);
	void	_handleLIST(Server& server, int fd, const string&);
	void	_handleINVITE(Server& server, int fd, const string&);
	void	_handleKICK(Server& server, int fd, const string&);
	void	_handlePING(Server& server, int fd, const string&);
	void	_handleJOIN(Server& server, int fd, const string&);
	void	_handleQUIT(Server& server, int fd, const string&);
	void	_handlePART(Server& server, int fd, const string&);
	void	_handleNOTICE(Server& server, int fd, const string&);
	void	_handlePASS(Server& server, int fd, const string&);
	void	_handleUSER(Server& server, int fd, const string&);

	void	_sendMessage(int fd, int type, const string &msg, const Server &server);

public:
	Command();
	void execute(Server& server, int fd, const string& msg);
};

#endif
