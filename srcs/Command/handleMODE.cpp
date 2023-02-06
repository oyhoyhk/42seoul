#include "Command.hpp"
#include "Utils.hpp"

void Command::_handleMODE(Server &server, int fd, const string &msg) {
    // user, channel 구분: 시작 '#'
    vector<string> words = split(msg, " ");
    string target = words[1];

    if (target[0] != '#') {	// USER MODE
        User* user = _service.getUserWithFD(fd);
		User* targetUser;
		try {
			targetUser = _service.getUserWithName(target);
		} catch (const exception& e) {
            // :irc.local 401 yubchoi2 noname :No such nick/channel
            string res(target + " :No such nick/channel\n");
            sendMessage(fd, res);
            return ;
		}
		string targetNickname = targetUser->getName();
		string nickname = user->getName();
        // user nickname과 명령어를 보낸 nickname 같은지 확인
        if (targetNickname != nickname) {
            // :irc.local 502 nickname_ :Can't change mode for other users / :Can't view modes for other users
			string res = nickname;
			if (words.size() == 2) {
				res += " :Can't view modes for other users\n";
			} else {
				res += " :Can't change mode for other users\n";
			}
			sendMessage(fd, res);
            return ;
        }

		// "/mode yubchoi" -> "yubchoi :+i / :+"
		if (words.size() == 2) {
			string res = nickname + " :+";
			if (user->isSetMode((UserMode)USER_MODE_I)) {
				res += "i";
			} else if (user->isSetMode((UserMode)USER_MODE_S)) {
				res += "s";
			} else if (user->isSetMode((UserMode)USER_MODE_W)) {
				res += "w";
			} else if (user->isSetMode((UserMode)USER_MODE_O)) {
				res += "o";
			}
			res += "\n";
			sendMessage(fd, res);
			return ;
		}

        // mode 검사
		string newMode = words[2];
		string addMode = "+";
		string removeMode = "-";
		string res = "";
        for (int i = 0; i < newMode.length(); i++) {
            if (newMode[i] == 'i') {
				// cout << "userMode: " << user->isSetMode((UserMode)USER_MODE_I) << endl;	// TEST
                if (i > 0 && newMode[i-1] == '-' && user->isSetMode(USER_I)) {
                    // TODO: user->setInvisible(false);
					// cout << "remove invisible" << endl; // TEST
					removeMode += "i";
                } else if (user->isSetMode(USER_I) == 0) {                    
                    // TODO: user->setInvisible(true);
					// cout << "add invisible" << endl;	// TEST
					addMode += "i";
                }
            } else if (newMode[i] == 'w') {
                if (i && newMode[i-1] == '-' && user->isSetMode((UserMode)USER_MODE_W)) {
                    // TODO: user->setReceiveWallops(false);
					removeMode += "w";
                } else if (user->isSetMode((UserMode)USER_MODE_W) == 0) {
                    // TODO: user.setReceiveWallops(true);
					addMode += "w";
                }
            } else if (newMode[i] == 'o') {
                if (i && newMode[i-1] == '-' && user->isSetMode((UserMode)USER_MODE_O)) {
                    // TODO: user->setOperator(false);
					removeMode += "o";
                } else if (user->isSetMode((UserMode)USER_MODE_O) == 0) {
                    // TODO: user->setOperator(true);
					addMode += "o";
                }
            } else if (newMode[i] == 's') {
                if (i && newMode[i-1] == '-' && user->isSetMode((UserMode)USER_MODE_S)) {
					// TODO: serviceNotice
					removeMode += "s";
                } else if (user->isSetMode((UserMode)USER_MODE_S) == 0) {
					// TODO: serviceNotice
					addMode += "s";
                }
            } else if (newMode[i] == '+' || newMode[i] == '-') {
				continue;
			} else { // yubchoi j :is unknown mode char to me
				res += nickname + " " + newMode[i] + " :is unknown mode char to me\n";
			}
        }
        
		if (addMode.length() > 1) {
			res += "MODE " + nickname + " " + addMode + "\n";
		}
		if (removeMode.length() > 1) {
			res += "MODE " + nickname + " " + removeMode + "\n";
		}
		sendMessage(fd, res);
		cout << "OUTPUT: " << res; // TEST
		return;
    } else {
        // channel MODE: _handleChannelMode()

    }
}