#include "Server.hpp"

void	Server::handleCAP(int i) {
	(void) i;
	std::cout << "CAP!!!!" <<std::endl;
}

void	Server::handleNICK(int i) {
	//vector<User *>::iterator iter;
	(void) i;
	//for (iter = _userList.begin(); iter != _userList.end(); ++iter) {
	//	if ((*iter)->getNickname() == )
	//}
	//const char *tempChar = ":irc.local 433 * ace :Nickname is already in use.\n";
	//for (int j = 1; j < MAX_FD_SIZE; ++j) {
	//	if (_pollFDs[j].fd != -1 && _pollFDs[i].fd == _pollFDs[j].fd) {
	//		write(_pollFDs[j].fd, tempChar, strlen(tempChar));
	//	}
	//}
}

void	Server::handlePRIVMSG(int i) {
	(void) i;
	std::cout << "PRIVMSG!!!" <<std::endl;
}

void	Server::handleLIST(int i) {
	(void) i;
	std::cout << "LIST!!!" <<std::endl;
}

void	Server::handleINVITE(int i) {
	(void) i;
	std::cout << "INVITE!!!" <<std::endl;
}

void	Server::handleKICK(int i) {
	(void) i;
	std::cout << "KICK!!!" <<std::endl;
}

void	Server::handlePING(int i) {
	(void) i;
	std::cout << "PING!!!" <<std::endl;
}

void	Server::handleJOIN(int i) {
	(void) i;
	std::cout << "JOIN!!!" <<std::endl;
}

void	Server::handleQUIT(int i) {
	(void) i;
	std::cout << "QUIT!!!" <<std::endl;
}


void	Server::handlePART(int i) {
	(void) i;
	std::cout << "PART!!!" <<std::endl;
}

void	Server::handleNOTICE(int i) {
	(void) i;
	std::cout << "NOTICE!!!" <<std::endl;
}


void	Server::handlePASS(int i) {
	(void) i;
	std::cout << "PASS!!!" <<std::endl;
}

void	Server::handleUSER(int i) {
	(void) i;
	std::cout << "USER!!!" <<std::endl;
}