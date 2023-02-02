#include "Server.hpp"

void	Server::handleCAP(int i, std::string msg) {
	(void) i;
	
	std::cout << msg << std::endl;
}

void	Server::handleNICK(int i, std::string msg) {
	(void) i;
	
	std::cout << msg << std::endl;
	std::vector<std::string> result = split(msg, " ");
	_nicknameList[i] = result.at(1);
}

void	Server::handlePRIVMSG(int i, std::string msg) {
	(void) i;
	std::cout << "PRIVMSG!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Server::handleLIST(int i, std::string msg) {
	(void) i;
	std::cout << "LIST!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Server::handleINVITE(int i, std::string msg) {
	(void) i;
	std::cout << "INVITE!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Server::handleKICK(int i, std::string msg) {
	(void) i;
	std::cout << "KICK!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Server::handlePING(int i, std::string msg) {
	(void) i;
	std::cout<<msg<<std::endl;
	const char *res = ":irc.local PONG irc.local :irc.local";
	for(int j=1;j<MAX_FD_SIZE;++j) {
		if(_pollFDs[j].fd != -1 && _pollFDs[i].fd == _pollFDs[j].fd) {
			write(_pollFDs[j].fd, res, strlen(res));
		}
	}
}

void	Server::handleJOIN(int i, std::string msg) {
	(void) i;
	std::cout << "JOIN!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Server::handleQUIT(int i, std::string msg) {
	(void) i;
	std::cout << "QUIT!!!" <<std::endl;
	std::cout << msg << std::endl;
}


void	Server::handlePART(int i, std::string msg) {
	(void) i;
	std::cout << "PART!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Server::handleNOTICE(int i, std::string msg) {
	(void) i;
	std::cout << "NOTICE!!!" <<std::endl;
	std::cout << msg << std::endl;
}


void	Server::handlePASS(int i, std::string msg) {
	(void) i;
	std::cout << "PASS!!!" <<std::endl;
	std::cout << msg << std::endl;
}

void	Server::handleUSER(int i, std::string msg) {
	std::cout <<msg<< std::endl;
	std::vector<std::string> list;
	list.push_back((":irc.local 001 " + _nicknameList[i] + " :Welcome to the Localnet IRC Network " + _nicknameList[i] + "!root@127.0.0.1\n"));
	list.push_back(":irc.local 002 " + _nicknameList[i] + " :Your host is irc.local, running version InspIRCd-3\n");
	list.push_back(":irc.local 003 " + _nicknameList[i] + " :This server was created 00:29:04 Feb 02 2023\n");
	list.push_back(":irc.local 004 " + _nicknameList[i] + " irc.local InspIRCd-3 iosw biklmnopstv :bklov\n");
	list.push_back(":irc.local 005 " + _nicknameList[i] + " AWAYLEN=200 CASEMAPPING=rfc1459 CHANLIMIT=#:20 CHANMODES=b,k,l,imnpst CHANNELLEN=64 CHANTYPES=# ELIST=CMNTU HOSTLEN=64 KEYLEN=32 KICKLEN=255 LINELEN=512 MAXLIST=b:100 :are supported by this server\n");
	list.push_back(":irc.local 005 " + _nicknameList[i] + " MAXTARGETS=20 MODES=20 NAMELEN=128 NETWORK=Localnet NICKLEN=30 PREFIX=(ov)@+ SAFELIST STATUSMSG=@+ TOPICLEN=307 USERLEN=10 USERMODES=,,s,iow WHOX :are supported by this server\n");
	list.push_back(":irc.local 251 " + _nicknameList[i] + " :There are 0 users and 0 invisible on 1 servers\n");
	list.push_back(":irc.local 253 " + _nicknameList[i] + " 1 :unknown connections\n");
	list.push_back(":irc.local 254 " + _nicknameList[i] + " 0 :channels formed\n");
	list.push_back(":irc.local 255 " + _nicknameList[i] + " :I have 0 clients and 0 servers\n");
	list.push_back(":irc.local 265 " + _nicknameList[i] + " :Current local users: 0  Max: 1\n");
	list.push_back(":irc.local 266 " + _nicknameList[i] + " :Current global users: 0  Max: 1\n");
	list.push_back(":irc.local 375 " + _nicknameList[i] + " :irc.local message of the day\n");
	list.push_back(":irc.local 372 " + _nicknameList[i] + " : **************************************************\n");
	list.push_back(":irc.local 372 " + _nicknameList[i] + " : *             H    E    L    L    O              *\n");
	list.push_back(":irc.local 372 " + _nicknameList[i] + " : *  This is a private irc server. Please contact  *\n");
	list.push_back(":irc.local 372 " + _nicknameList[i] + " : *  the admin of the server for any questions or  *\n");
	list.push_back(":irc.local 372 " + _nicknameList[i] + " : *  issues.                                       *\n");
	list.push_back(":irc.local 372 " + _nicknameList[i] + " : **************************************************\n");
	list.push_back(":irc.local 372 " + _nicknameList[i] + " : *  The software was provided as a package of     *\n");
	list.push_back(":irc.local 372 " + _nicknameList[i] + " : *  Debian GNU/Linux <https://www.debian.org/>.   *\n");
	list.push_back(":irc.local 372 " + _nicknameList[i] + " : *  However, Debian has no control over this      *\n");
	list.push_back(":irc.local 372 " + _nicknameList[i] + " : *  server.                                       *\n");
	list.push_back(":irc.local 372 " + _nicknameList[i] + " : **************************************************\n");
	list.push_back(":irc.local 372 " + _nicknameList[i] + " : (The sysadmin possibly wants to edit </etc/inspircd/inspircd.motd>)\n");
	list.push_back(":irc.local 376 " + _nicknameList[i] + " :End of message of the day.\n");
	list.push_back(":irc.local PRIVMSG) " + _nicknameList[i] + " :*** Raw I/O logging is enabled on this server. All messages, passwords, and commands are being recorded.\n");
	std::vector<std::string>::iterator it;
	for(int j=1;j<MAX_FD_SIZE;++j) {
		if(_pollFDs[j].fd != -1 && _pollFDs[i].fd == _pollFDs[j].fd) {
			for(it=list.begin();it!=list.end();++it)
				write(_pollFDs[j].fd, (*it).c_str(), strlen((*it).c_str()));
		}
	}
	std::cout << "USER!!!" <<std::endl;
}