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

void Command::_handleQUIT(Server &server, int fd, const string &msg) {
    string 			              message;
    map<string, User>      		sended;
	string			              endMsg      =	 msg.substr(msg.find(":") + 1, msg.size());
    map<string, Channel>       userChannels    = server.getUserManager().getUserWithFD(fd).getChannel();

	message = "ERROR :Closing link: (" + string(HOST_NAME) + ") [Quit: " + endMsg + "]";
    write(fd, message.c_str(), strlen(message.c_str()));

    sended[server.getUserManager().getUserWithFD(fd).getName()] = server.getUserManager().getUserWithFD(fd);
	// quit하는 유저가 속하는 채널을 돌면서, 채널에 있는 유저를 중복허용하지 않고 write();
	for (map<string, Channel>::const_iterator cIt = userChannels.begin(); cIt != userChannels.end(); ++cIt) {
        for (map<string, User>::const_iterator uIt = cIt->second.getUsers().begin(); uIt != cIt->second.getUsers().end(); ++uIt) {
            if (sended.find(uIt->first) == sended.end()) {
                message = ":" + server.getUserManager().getUserWithFD(fd).getName() + "!" + string(HOST_NAME) + "QUIT :Quit: " + endMsg;
                sended[uIt->first] = uIt->second;
                write(uIt->second.getFD(), message.c_str(), strlen(message.c_str()));
            }
        }
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

	isChannel = (taker[1][0] == '#');
    if (isChannel) {
        // 채널이 존재하면, 채널 멤버 받고, 모두에게 뿌리기.
        if (server.getChannels().find(taker[1]) != server.getChannels().end()) {
            map<string, User> channelToSend = server.getChannels().find(taker[1])->second.getUsers();
            noticeMsg = ":" + server.getUserManager().getUserWithFD(fd).getName() + "!" + HOST_NAME + msg;

            for (map<string, User>::iterator it = channelToSend.begin(); it != channelToSend.end(); ++it) {
                if (it->second.getFD() == fd)
                    continue ;
                write(it->second.getFD(), noticeMsg.c_str(),strlen(noticeMsg.c_str()));
            }
        } else {
            noticeMsg = ":irc.local 401 " + server.getUserManager().getUserWithFD(fd).getName() + " " + taker[1] + " :No such nick/channel";
            write(fd, noticeMsg.c_str(), strlen(noticeMsg.c_str()));
        }
    } else {
        // 개인에게 보내면 개인에게 문자 보내기
        if (server.getUserManager().getUsers().find(taker[1]) != server.getUserManager().getUsers().end()) {
            noticeMsg = ":" + server.getUserManager().getUserWithFD(fd).getName() + "!" + HOST_NAME + msg;
            write(server.getUserManager().getUsers().find(taker[1])->second.getFD(), noticeMsg.c_str(), strlen(noticeMsg.c_str()));
        } else {
            noticeMsg = ":irc.local 401 " + server.getUserManager().getUserWithFD(fd).getName() + " " + taker[1] + " :No suchnick/channel";
            write(fd, noticeMsg.c_str(), strlen(noticeMsg.c_str()));
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

void Command::_handleMode(Server &server, int fd, const string &msg) {
    
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