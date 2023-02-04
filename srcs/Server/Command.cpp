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
    _cmds["MODE"] = &Command::_handleMODE;
}

static void sendMessage(const int& fd, const string& msg) {
    const char *temp = msg.c_str();
    write(fd, temp, strlen(temp));
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
    // TODO: 유저가 없을 경우 try catch를 써야하나?
    User user = userManager.getUserWithFD(fd);
	cout<<"can reach here?"<<endl;
    string newNickname = result.at(1);
    string oldNickname = user.getName();
    string response;
	(void) fd;

    // "/nick"
    if (result.size() <= 1) {
        // ERR_NONICKNAMEGIVEN, 431,  :No nickname given
        response = string(SERVER_PREFIX) + " 431 " + oldNickname + " :No nickname given";
        cout << response << endl;
        return;
    }

	if (userManager.nameDupCheck(result.at(1))) {
        response = string(SERVER_PREFIX) + " 433 " + oldNickname + " " + newNickname +
                 " :Nickname is already in use";
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

    // "/nick existingnickname"
    try {
       userManager.getUserWithName(oldNickname);
       // :irc.local 433 <nickname> <nickname> :Nickname is already in use
       response = string(SERVER_PREFIX) + " 433 " + oldNickname + " " + newNickname +
                " :Nickname is already in use";
       cout << response << endl;
		return;
    } catch (exception &e) {
       // "/nick newnickname"
		// TODO: string userInfo = user.getUserInfo();
		if (user.getMode() == NEED_NICKNAME) {
			response = "NICK " + newNickname;
			user.setMode(NEED_USERREGISTER);
		} else {
			response = ":" + string(HOST_NAME) + " NICK " + newNickname;
		}
		cout << response << endl;
    }
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
    map<string, Channel>& allChannel = server.getChannels();
    vector<string>        msgChannel = split(msg, " ");

    // 모든 채널에서 이름으로 조회해서 없으면
    if (allChannel.find(msgChannel[1]) == allChannel.end()) {
        /*
        1. 채널이 invite-only인 경우 초대를 꼭 받아야함.
        2. active-bans에 유저의 /nick/username/hostname이 없어야한다.
        3. 비밀번호가 설정되어 있는 채널이면 올바른 비밀번호를 입력해야한다.
        */

        // 채널배열에 새로운 채널 넣음.
        allChannel[msgChannel[1]] = Channel(msgChannel[1]);
        // JOIN하려는 유저객체에 joinChannel()
        server.getUserManager().getUserWithFD(fd).joinChannel(msgChannel[1]);
    } else {
        // JOIN하려는 유저객체에 joinChannel()
        server.getUserManager().getUserWithFD(fd).joinChannel(msgChannel[1]);
    }
}

/* 유저가 없으면 throw함 나중에 처리할 필요가 있음 */ 
void Command::_handleQUIT(Server &server, int fd, const string &msg) {
	string              endMsg      = msg.substr(msg.find(":") + 1, msg.size());
	string              message     = "ERROR :Closing link: (" + string(HOST_NAME) + ") [Quit: " + endMsg + "]";
    User*               reqUser     = _service.getUserWithFD(fd);
    string              reqUserName = reqUser->getName(); 
    vector<Channel*>    channels    = reqUser->getChannels();
    vector<User*>       tempUsers;
    set<User*>          targetUsers;

    _service.deleteUserWithName(reqUserName);
    sendMessage(fd, message);
    for (vector<Channel*>::iterator iter = channels.begin(); iter != channels.end(); ++iter) {
        tempUsers = (*iter)->getUsers();
        targetUsers.insert(tempUsers.begin(), tempUsers.end());
    }
    for (set<User*>::iterator iter = targetUsers.begin(); iter != targetUsers.end(); ++iter) {
        message = ":" + reqUserName + "!" + string(HOST_NAME) + "QUIT :Quit: " + endMsg;
        sendMessage((*iter)->getFD(), message);
    }
}


void Command::_handlePART(Server &server, int fd, const string &msg) {
    (void)fd;
    (void)server;

    cout << "PART!!!" << endl;
    cout << msg << endl;
    
}

void Command::_handleNOTICE(Server &server, int fd, const string &msg) {
	bool			isChannel;
	vector<string>	taker = split(msg, " ");
	string 			noticeMsg;
    User*           sender = _service.getUserWithFD(fd);
    const string&   target = taker[1];

    /* 두가지로 나뉘는데 그 안에 두가지가 또 있어 그 두가지 형태가 같아요 그래서 함수로 만들까 하다다가 안했다*/
    /* Notice 받는사람 메시지 */
	isChannel = (taker[1][0] == '#');
    if (isChannel) {
        // 채널이 존재하면, 채널 멤버 받고, 모두에게 뿌리기.
        try {
            Channel* channel = _service.getChannelWithName(target);
            vector<User*> users = channel->getUsers();
            noticeMsg = ":" + sender->getName() + "!" + HOST_NAME + msg;
            for (vector<User*>::iterator iter = users.begin(); iter != users.end(); iter++)
                if ((*iter) != sender) sendMessage((*iter)->getFD(), noticeMsg);
        } catch (const exception& e) {
            noticeMsg = ":irc.local 401 " + sender->getName() + " " + target + " :No such nick/channel";
            sendMessage(fd, noticeMsg);
        }
    } else {
        // 개인에게 보내면 개인에게 문자 보내기
        try {
            User* user = _service.getUserWithName(target);
            noticeMsg = ":" + sender->getName() + "!" + HOST_NAME + msg;
            sendMessage(user->getFD(), noticeMsg);
        } catch (const exception& e) {
            noticeMsg = ":irc.local 401 " + sender->getName() + " " + target + " :No suchnick/channel";
            sendMessage(fd, noticeMsg);
        }
    }
}

void Command::_handlePASS(Server &server, int fd, const string &msg) {
    (void)fd;
    (void)server;
    vector<string> result = split(msg, " ");
    const string &inputPassword = result.at(1);

    if (server.getPassword() != inputPassword) {
        string res("Password Wrong\r\n");
        _sendMessage(fd, RES_SELF, res, server);
        return;
    }
    cout << "PASS!!!" << endl;
}

void Command::_handleUSER(Server &server, int fd, const string &msg) {
    cout << msg << endl;
    vector<string> list;
    // const string &userName =
    server.getUserManager().getUserWithFD(fd).getName();
    list.push_back((":irc.local 001 " + userName +
                    " :Welcome to the Localnet IRC Network " + userName +
                    "!root@127.0.0.1\n"));
    vector<string>::iterator it;
    for (it = list.begin(); it != list.end(); ++it)
        write(fd, (*it).c_str(), strlen((*it).c_str()));
    cout << "USER!!!" << endl;
}

void Command::_handleMODE(Server &server, int fd, const string &msg) {
    // user, channel 구분: 시작 '#'
    vector<string> words = split(msg, " ");
    const string& targetName = words[1];
    const string& targetMode = words[2];
    User* user = NULL;
    User* target = NULL;

    if (targetName[0] != '#') {
        // user MODE: _handleUserMode()
        user = _service.getUserWithFD(fd);
        try {
            target = _service.getUserWithName(targetName);
        } catch (const exception& e) {
            string res = SERVER_PREFIX + string(" 401 ") + user->getName() + " " + targetName + " :No such nick/channel\n";
            sendMessage(fd, res);
            return ;
        }
        
        // user nickname과 명령어를 보낸 nickname 같은지 확인
        if (user->getName() != targetName) {
            // :irc.local 502 nickname_ :Can't change mode for other users
            string res(SERVER_PREFIX + string(" 502 ") + user->getName() + " :Can't change mode for other users\n");
            sendMessage(fd, res);
            return ;
        }

        // mode 검사
        for (int i = 0; i < targetMode.length(); i++) {
            switch (targetMode[i]) {
            case 'i':
                -iows -i-o+s  ios
                break;
            case 'w':
                break;
            case 'o':
                break;
            case 's':
                break;
            case '-':
            case '+':
                break;
            default:
            }
            if (words[2][i] != 'i' && words[2][i] != 'w' && words[2][i] != 'o' && words[2][i] != 's' && words[2][i] != '+' && words[2][i] != '-') {
                // :irc.local 501 nickname_ :Unknown MODE flag
                string res(SERVER_PREFIX + string(" 501 ") + nickname + string(" :Unknown MODE flag\n"));
                _sendMessage(fd, RES_SELF, res, server);
                continue;
            }
            // find i
            else if (words[2][i] == 'i') {
                if (i && words[2][i-1] == '-' && user.mode[USER_MODE_I]) {
                    user.setInvisible(false);
                    // :nickname_!root@127.0.0.1 MODE nickname_ -i
                    _sendMessage(fd, RES_SELF, string(user.), server);
                } else if (user.mode[USER_MODE_I] == 0) {                    
                    user.setInvisible(true);
                }
            } else if (words[2][i] == 'w') {
                if (i && words[2][i-1] == '-' && user.mode[USER_MODE_W]) {
                    user.setReceiveWallops(false);
                } else if (user.mode[USER_MODE_W] == 0) {
                    user.setReceiveWallops(true);
                }
            } else if (words[2][i] == 'o') {
                if (i && words[2][i-1] == '-' && user.mode[USER_MODE_O]) {
                    user.setOperator(false);
                } else if (user.mode[USER_MODE_O] == 0) {
                    user.setOperator(true);
                }
            } else if (words[2][i] == 's') {
                if (i && words[2][i-1] == '-' && user.mode[USER_MODE_S]) {
                    user.setInvisible(false);
                } else if (user.mode[USER_MODE_S] == 0) {
                    user.setInvisible(true);
                }
            }
        }
        
        
    } else {
        // channel MODE: _handleChannelMode()

    }
    // user MODE

    // 
}

void Command::_sendMessage(int fd, int type, const string &msg, const Server &server) {
    if (type == RES_SELF) {
        write(fd, msg.c_str(), strlen(msg.c_str()));
        return ;
    }
    const struct pollfd *pollFDs = server.getPollFDs();
    for (int i=1;i<MAX_FD_SIZE;i++) {
        if (pollFDs[i].fd != -1 && pollFDs[i].fd != fd) {
            write(i, msg.c_str(), strlen(msg.c_str()));
        }
    }
}