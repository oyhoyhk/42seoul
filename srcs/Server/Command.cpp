#include "Server/Command.hpp"
#include "Utils.hpp"

Command::Command() {
    _cmds["CAP"] = &Command::_handleCAP;
    _cmds["NICK"] = &Command::_handleNICK;
    _cmds["PRIVMSG"] = &Command::_handlePRIVMSG;
    _cmds["LIST"] = &Command::_handleLIST;
    _cmds["INVITE"] = &Command::_handleINVITE;
    _cmds["KICK"] = &Command::_handleKICK;
    _cmds["PING"] = &Command::_handlePING;
    _cmds["JOIN"] = &Command::_handleJOIN;
    _cmds["QUIT"] = &Command::_handleQUIT;
    _cmds["PART"] = &Command::_handlePART;
    _cmds["NOTICE"] = &Command::_handleNOTICE;
    _cmds["PASS"] = &Command::_handlePASS;
    _cmds["USER"] = &Command::_handleUSER;
}

void Command::execute(Server &server, int fd, const string &msg) {
    vector<string> words = split(msg, " ");
    iter_cmd cmd = _cmds.find(*words.begin());
    if (cmd != _cmds.end())
        (this->*(cmd->second))(server, fd, msg);
    else
        throw runtime_error("Command has not existed");
};

void Command::_handleCAP(Server &server, int fd, const string &msg) {
    (void)fd;
    (void)server;

    cout << msg << endl;
}

void Command::_handleNICK(Server &server, int fd, const string &msg) {
	UserManager userManager = server.getUserManager();
    vector<string> result = split(msg, " ");
    //User user = userManager.getUserWithFD(fd);
	cout<<"can reach here?"<<endl;
    string newNickname;
    string oldNickname = "*";
    // 기존 아이디가 있으면 *을 기존 아이디로 대체
    //if (user.getName()) {
    //    oldNickname = user.getName();
    //}
    string response;
	(void) fd;
	// 
	if (userManager.nameDupCheck(result.at(1))) {
        response = string(SERVER_PREFIX) + " 433 " + oldNickname + " " + newNickname +
                 " :Nickname is already in use";
        cout << response << endl;
		return;		
	}

    // TODO: getServerPrefix

    // "/nick"
    if (result.size() <= 1) {
        // ERR_NONICKNAMEGIVEN, 431,  :No nickname given
        response = string(SERVER_PREFIX) + " 431 " + oldNickname + " :No nickname given";
        cout << response << endl;
        return;
    }

    newNickname = result.at(1);
    // "/nick morethan9letters"
    if (newNickname.length() > 9) {
        // :irc.local 432 <nickname> <nickname> :Erroneus nickname
        response = string(SERVER_PREFIX) + " 432 " + oldNickname + " " + newNickname +
                 " :Erroneus nickname";
		cout << response << endl;
        return;
    }

    //// "/nick existingnickname"
    //try {
    //    userManager.getUserWithName(oldNickname);
    //    // :irc.local 433 <nickname> <nickname> :Nickname is already in use
    //    response = string(SERVER_PREFIX) + " 433 " + oldNickname + " " + newNickname +
    //             " :Nickname is already in use";
    //    cout << response << endl;
	//	return;
    //} catch (exception &e) {
    //    // "/nick newnickname"
	//	// TODO: string userInfo = user.getUserInfo();
	//	if (user.getMode() == NEED_NICKNAME) {
	//		response = "NICK " + newNickname;
	//		user.setMode(NEED_USERREGISTER);
	//	} else {
	//		response = ":" + string(HOST_NAME) + " NICK " + newNickname;
	//	}
	//	cout << response << endl;
    //}
}

void Command::_handlePRIVMSG(Server &server, int fd, const string &msg) {
    (void)fd;
    (void)server;

    cout << "PRIVMSG!!!" << endl;
    cout << msg << endl;
}

void Command::_handleLIST(Server &server, int fd, const string &msg) {
    (void)fd;
    (void)server;

    cout << "LIST!!!" << endl;
    cout << msg << endl;
}

void Command::_handleINVITE(Server &server, int fd, const string &msg) {
    (void)fd;
    (void)server;

    cout << "INVITE!!!" << endl;
    cout << msg << endl;
}

void Command::_handleKICK(Server &server, int fd, const string &msg) {
    (void)fd;
    (void)server;

    cout << "KICK!!!" << endl;
    cout << msg << endl;
}

void Command::_handlePING(Server &server, int fd, const string &msg) {
    (void)server;

    cout << msg << endl;
    const char *res = ":irc.local PONG irc.local :irc.local";
    write(fd, res, strlen(res));
}

void Command::_handleJOIN(Server &server, int fd, const string &msg) {
    (void)fd;
    (void)server;

    cout << "JOIN!!!" << endl;
    cout << msg << endl;
}

void Command::_handleQUIT(Server &server, int fd, const string &msg) {
    (void)fd;
    (void)server;
	cout << msg <<  endl;

    // string 				Qmsg 		= msg.substr(6, msg.size() - 6);
	// vector<string> 	userChannel = server.getUserManager().getUserWithFD(fd).getChannel();
    // string 				message;
	// map<string>		sended;
	// string					endMsg =	 msg.substr(msg.find(":") + 1, msg.size());


	/* TODO */
	// message = "ERROR :Closing link: (" + string(HOST_NAME) + ") [Quit: " + Qmsg + "]";
    // write(fd, message.c_str(), strlen(message.c_str()));
	// quit하는 유저가 속하는 채널을 돌면서, 채널에 있는 유저를 중복허용하지 않고 write();
	// for (vector<string>::iterator UCit = userChannel.begin(); UCit != userChannel.end(); ++UCit) {
	// 	for (map<string, User>::iterator userIt = UCit.begin(); userIt != UCit.end(); ++userIt) {
			
	// 	}
}


void Command::_handlePART(Server &server, int fd, const string &msg) {
    (void)fd;
    (void)server;

    cout << "PART!!!" << endl;
    cout << msg << endl;
}

void Command::_handleNOTICE(Server &server, int fd, const string &msg) {
    (void)fd;
    (void)server;

    cout << "NOTICE!!!" << endl;
    cout << msg << endl;
}

// 필요한 함수, 방이름 있는지 찾아주는 함수, 개인이름 있는지 확인하는 함수,
// 방에 있는 멤버 보내주는 함수 void	Server::handleNOTICE(int i,
// string msg) { 	(void) i;

// 	bool						isRoom;
// 	vector<string>	taker = split(msg, " ");
// 	string 				noticeMsg;

// 	isRoom = (taker[1][0] == '#');
// 	for(int j=1;j<MAX_FD_SIZE;++j) {
// 		if(_pollFDs[j].fd != -1 && _pollFDs[i].fd == _pollFDs[j].fd) {
// 			if (isRoom) {
// 				// 방이름은 무조건 앞에 #가 붙어있는 채로 저장.
// 이렇게 하면 보내고 받을 때 편함. 				if
// (isRoomThere(taker[1])) { vector<member> roomMem =
// getRoomMember(taker[1]); 					noticeMsg =
// ":"
// + 보낸사람이름 +
// "!root@127.0.0.1" + msg; 					for (member
// mem : roomMem) { 						if
// (mem.getFd()
// == _pollFDs[j].fd)
// continue ; write(mem.getFd(), noticeMsg.c_str(),
// strlen(noticeMsg.c_str()));
// 					}
// 				} else {
// 					noticeMsg = ":irc.local 401 " +
// 보낸사람이름
// +
// "
// "
// +
// 룸이름 + " :No such nick/channel";
// write(_pollFDs[j].fd, noticeMsg.c_str(), strlen(noticeMsg.c_str()));
// 				}
// 			} else {
// 				if (isMemberThere(taker[1])) {
// 					noticeMsg = ":" + 보내는사람이름 +
// "!root@127.0.0.1"
// + msg; 					write(받는사람.getFd(),
// noticeMsg.c_str(),
// strlen(noticeMsg.c_str())); 				} else {
// noticeMsg = ":irc.local 401 " + 보낸사람이름 + " " + 룸이름 + " :No such
// nick/channel"; write(_pollFDs[j].fd, noticeMsg.c_str(),
// strlen(noticeMsg.c_str()));
// 				}
// 			}
// 		}
// 	}
// }

void Command::_handlePASS(Server &server, int fd, const string &msg) {
    (void)fd;
    (void)server;

    cout << "PASS!!!" << endl;
    cout << msg << endl;
}

void Command::_handleUSER(Server &server, int fd, const string &msg) {
    cout << msg << endl;
    vector<string> list;
    const string &userName =
        server.getUserManager().getUserWithFD(fd).getName();
    list.push_back((":irc.local 001 " + userName +
                    " :Welcome to the Localnet IRC Network " + userName +
                    "!root@127.0.0.1\n"));
    vector<string>::iterator it;
    for (it = list.begin(); it != list.end(); ++it)
        write(fd, (*it).c_str(), strlen((*it).c_str()));
    cout << "USER!!!" << endl;
}
