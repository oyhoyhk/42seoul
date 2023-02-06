#include "Command.hpp"
#include "Utils.hpp"
#include "ReplieFactory.hpp"

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
			res += ERR_USERSDONTMATCH_502();
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
                    user->unsetMode(USER_I);
					// cout << "remove invisible" << endl; // TEST
					removeMode += "i";
                } else if (user->isSetMode(USER_I) == 0) {                    
                    user->setMode(USER_I);
					// cout << "add invisible" << endl;	// TEST
					addMode += "i";
                }
            } else if (newMode[i] == 'w') {
                if (i && newMode[i-1] == '-' && user->isSetMode(USER_W)) {
                    // TODO: user->setReceiveWallops(false);
					user->unsetMode(USER_W);
					removeMode += "w";
                } else if (user->isSetMode(USER_W) == 0) {
                    // TODO: user.setReceiveWallops(true);
					user->setMode(USER_W);
					addMode += "w";
                }
            } else if (newMode[i] == 'o') {
                if (i && newMode[i-1] == '-' && user->isSetMode(USER_O)) {
                    // TODO: user->setOperator(false);
					user->unsetMode(USER_O);
					removeMode += "o";
                } else if (user->isSetMode(USER_O) == 0) {
                    // TODO: user->setOperator(true);
					user->setMode(USER_O);
					addMode += "o";
                }
            } else if (newMode[i] == 's') {
                if (i && newMode[i-1] == '-' && user->isSetMode(USER_S)) {
					user->unsetMode(USER_S);
					removeMode += "s";
                } else if (user->isSetMode(USER_S) == 0) {
					user->setMode(USER_S);
					addMode += "s";
                }
            } else if (newMode[i] == '+' || newMode[i] == '-') {
				continue;
			} else { // yubchoi j :is unknown mode char to me
				// replieFactory
				res += ERR_UNKNOWNMODE_472(newMode[i]);
			}
        }
        
		if (addMode.length() > 1) {
			res += "MODE " + nickname + " " + addMode + "\n";
		}
		if (removeMode.length() > 1) {
			res += "MODE " + nickname + " " + removeMode + "\n";
		}
		sendMessage(fd, res);
		// cout << "OUTPUT: " << res; // TEST
		return;
    } else {
        // channel MODE: _handleChannelMode()

    }
}