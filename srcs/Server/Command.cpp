#include "Server/Command.hpp"

Command::Command() {
	_cmds["CAP"]		= &Command::_handleCAP;
	_cmds["NICK"] 		= &Command::_handleNICK;
	_cmds["PRIVMSG"]	= &Command::_handlePRIVMSG;
	_cmds["LIST"]		= &Command::_handleLIST;
	_cmds["INVITE"]		= &Command::_handleINVITE;
	_cmds["KICK"]		= &Command::_handleKICK;
	_cmds["PING"]		= &Command::_handlePING;
	_cmds["JOIN"]		= &Command::_handleJOIN;
	_cmds["QUIT"]		= &Command::_handleQUIT;
	_cmds["PART"]		= &Command::_handlePART;
	_cmds["NOTICE"]		= &Command::_handleNOTICE;
	_cmds["PASS"]		= &Command::_handlePASS;
	_cmds["USER"]		= &Command::_handleUSER;
}

void Command::execute(Server& server,  int fd, const std::string& msg) {
	std::vector<std::string> words = split(msg, " ");
	iter_cmd cmd = _cmds.find(*words.begin());
	if (cmd != _cmds.end()) (this->*(cmd->second))(server, fd, msg);
	else throw std::runtime_error("Command has not existed");
};

void	Command::_handleCAP(Server& server, int fd, const std::string& msg) {
	(void) fd;
	(void) server;

	std::cout << msg << std::endl;
}

void	Command::_handleNICK(Server& server, int fd, const std::string& msg) {
	(void) fd;
	(void) server;

	std::cout << msg << std::endl;
	std::vector<std::string> result = split(msg, " ");
	server.getUserManager().addUser(result.at(1), fd);
}

void	Command::_handlePRIVMSG(Server& server, int fd, const std::string& msg) {
	(void) fd;
	(void) server;

	std::cout << "PRIVMSG!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Command::_handleLIST(Server& server, int fd, const std::string& msg) {
	(void) fd;
	(void) server;

	std::cout << "LIST!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Command::_handleINVITE(Server& server, int fd, const std::string& msg) {
	(void) fd;
	(void) server;

	std::cout << "INVITE!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Command::_handleKICK(Server& server, int fd, const std::string& msg) {
	(void) fd;
	(void) server;

	std::cout << "KICK!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Command::_handlePING(Server& server, int fd, const std::string& msg) {
	(void) server;

	std::cout<<msg<<std::endl;
	const char *res = ":irc.local PONG irc.local :irc.local";
	write(fd, res, strlen(res));
}

void	Command::_handleJOIN(Server& server, int fd, const std::string& msg) {
	(void) fd;
	(void) server;

	std::cout << "JOIN!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Command::_handleQUIT(Server& server, int fd, const std::string& msg) {
	(void) fd;
	(void) server;

	std::cout << "QUIT!!!" <<std::endl;
	std::cout << msg << std::endl;
}


void	Command::_handlePART(Server& server, int fd, const std::string& msg) {
	(void) fd;
	(void) server;

	std::cout << "PART!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Command::_handleNOTICE(Server& server, int fd, const std::string& msg) {
	(void) fd;
	(void) server;

	std::cout << "NOTICE!!!" <<std::endl;
	std::cout << msg << std::endl;
}


void	Command::_handlePASS(Server& server, int fd, const std::string& msg) {
	(void) fd;
	(void) server;

	std::cout << "PASS!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Command::_handleUSER(Server& server, int fd, const std::string& msg) {
	std::cout <<msg<< std::endl;
	std::vector<std::string> list;
	const std::string& userName = server.getUserManager().getUserWithFD(fd).getName();
	list.push_back((":irc.local 001 " + userName + " :Welcome to the Localnet IRC Network " + userName + "!root@127.0.0.1\n"));
	std::vector<std::string>::iterator it;
	for(it=list.begin();it!=list.end();++it)
		write(fd, (*it).c_str(), strlen((*it).c_str()));
	std::cout << "USER!!!" <<std::endl;
}
