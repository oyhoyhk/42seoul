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
	std::cout << msg;
	// void	Server::handleNICK(int i, std::string msg) {
	// (void) i;	// TEST??
	// std::string serverPrefix;
	// std::string newNickname;
	// std::string oldNickname = _nicknameList[i];
	// std::vector<std::string> tmp;
	
	// std::cout << msg << std::endl;	// TEST
	// std::vector<std::string> result = split(msg, " ");

	// // TODO: getServerPrefix
	// serverPrefix = "irc.local";	// TODO: delete (DUMMY)
	// // serverPrefix = getServerPrefix();

	// // "/nick"
	// if (result.size() <= 1) {
	// 	// ERR_NONICKNAMEGIVEN, 431,  :No nickname given
	// 	tmp.clear();
	// 	tmp.push_back(serverPrefix);
	// 	tmp.push_back("431");
	// 	tmp.push_back(ERR_NONICKNAMEGIVEN());
	// 	//ㅇㅣ거 괄호 맞나요?? 아아랫줄    {}   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// 	std::cout << join(tmp) << std::endl;
	// 	return;
	// }

	// newNickname = result.at(1);
	// // "/nick morethan9letters"
	// if (newNickname.length() > 9) {
	// 	// :irc.local 432 <nickname> <nickname> :Erroneus nickname
	// 	tmp.clear();
	// 	tmp.push_back(serverPrefix);
	// 	tmp.push_back("432");
	// 	tmp.push_back(oldNickname);
	// 	tmp.push_back(newNickname);
	// 	tmp.push_back(ERR_ERRONEUSNICKNAME());
	// 	std::cout << join(tmp) << std::endl;
	// 	return;
	// }

	// // "/nick existingnickname"
	// if (std::find(_nicknameList, _nicknameList + MAX_FD_SIZE, _nicknameList[i]) != _nicknameList + MAX_FD_SIZE) {
	// 	// :irc.local 433 <nickname> <nickname> :Nickname is already in use
	// 	tmp.clear();
	// 	tmp.push_back(serverPrefix);
	// 	tmp.push_back("433");
	// 	tmp.push_back(oldNickname);
	// 	tmp.push_back(newNickname);
	// 	tmp.push_back(ERR_NICKNAMEINUSE());
	// 	std::cout << join(tmp) << std::endl;
	// 	return;
	// }

	// // "/nick newnickname"
	// _nicknameList[i] = newNickname;
	// // TODO: setNickname
	// // getUser
	// std::string user;
	// user = "oldNick!root@127.0.0.1 NICK newNick";	// TODO: delete (DUMMY)
	// // user = getUser();
	// // 001
	// // std::cout << join({serverPrefix, "001", newNickname, "Welcome to the Internet Relay Network " + newNickname + "!"}) << std::endl;
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

// void	Server::handleQUIT(int i, std::string msg) {
// 	(void) i;

// 	std::string Qmsg = msg.assign(msg.begin() - 6, msg.end());

// 	std::string message;
// 	for(int j=1;j<MAX_FD_SIZE;++j) {
// 		if(_pollFDs[j].fd != -1 && _pollFDs[i].fd == _pollFDs[j].fd) {
// 			message = "ERROR :Closing link: (root@127.0.0.1) [Quit: " + Qmsg + "]";
// 			write(_pollFDs[j].fd, message.c_str(), strlen(message.c_str()));
			
// 			std::vector<member> roomMem = getRoomMember();
// 			if (roomMem.memSize() != 0) {
// 				std::string sendMsg = msg.substr(msg.find(":") + 1, msg.size());
// 				for (member mem : room) {
// 					write(mem.getFd(), sendMsg.c_str(), strlen(sendMsg.c_str()));
// 				}
// 			}
// 		}
// 	}
// }



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

// 필요한 함수, 방이름 있는지 찾아주는 함수, 개인이름 있는지 확인하는 함수, 방에 있는 멤버 보내주는 함수
// void	Server::handleNOTICE(int i, std::string msg) {
// 	(void) i;

// 	bool						isRoom;
// 	std::vector<std::string>	taker = split(msg, " ");
// 	std::string 				noticeMsg;

// 	isRoom = (taker[1][0] == '#');
// 	for(int j=1;j<MAX_FD_SIZE;++j) {
// 		if(_pollFDs[j].fd != -1 && _pollFDs[i].fd == _pollFDs[j].fd) {
// 			if (isRoom) {
// 				// 방이름은 무조건 앞에 #가 붙어있는 채로 저장. 이렇게 하면 보내고 받을 때 편함.
// 				if (isRoomThere(taker[1])) {
// 					std::vector<member> roomMem = getRoomMember(taker[1]);
// 					noticeMsg = ":" + 보낸사람이름 + "!root@127.0.0.1" + msg;
// 					for (member mem : roomMem) {
// 						if (mem.getFd() == _pollFDs[j].fd)
// 							continue ;
// 						write(mem.getFd(), noticeMsg.c_str(), strlen(noticeMsg.c_str()));
// 					}
// 				} else {
// 					noticeMsg = ":irc.local 401 " + 보낸사람이름 + " " + 룸이름 + " :No such nick/channel";
// 					write(_pollFDs[j].fd, noticeMsg.c_str(), strlen(noticeMsg.c_str()));
// 				}
// 			} else {
// 				if (isMemberThere(taker[1])) {
// 					noticeMsg = ":" + 보내는사람이름 + "!root@127.0.0.1" + msg;
// 					write(받는사람.getFd(), noticeMsg.c_str(), strlen(noticeMsg.c_str()));
// 				} else {
// 					noticeMsg = ":irc.local 401 " + 보낸사람이름 + " " + 룸이름 + " :No such nick/channel";
// 					write(_pollFDs[j].fd, noticeMsg.c_str(), strlen(noticeMsg.c_str()));
// 				}
// 			}
// 		}
// 	}
// }



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
