#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "header.hpp"
#include "Server/Server.hpp"
#include "Response.hpp"

class Server;

class Command {
private:
	typedef void(Command::*_pfunc)(Server& server, int, const std::string&);
	typedef std::map<std::string, _pfunc>::iterator iter_cmd;

	std::map<std::string, _pfunc>	_cmds;

	void	_handleNICK(Server& server, int fd, const std::string&);
	void	_handleCAP(Server& server, int fd, const std::string&);
	void	_handlePRIVMSG(Server& server, int fd, const std::string&);
	void	_handleLIST(Server& server, int fd, const std::string&);
	void	_handleINVITE(Server& server, int fd, const std::string&);
	void	_handleKICK(Server& server, int fd, const std::string&);
	void	_handlePING(Server& server, int fd, const std::string&);
	void	_handleJOIN(Server& server, int fd, const std::string&);
	void	_handleQUIT(Server& server, int fd, const std::string&);
	void	_handlePART(Server& server, int fd, const std::string&);
	void	_handleNOTICE(Server& server, int fd, const std::string&);
	void	_handlePASS(Server& server, int fd, const std::string&);
	void	_handleUSER(Server& server, int fd, const std::string&);

public:
	Command();
	void execute(Server& server, int fd, const std::string& msg);
};

#endif
