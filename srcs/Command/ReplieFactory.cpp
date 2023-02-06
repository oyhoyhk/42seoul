#include "Command/ReplieFactory.hpp"

inline static string join(const vector<string>& emts) {
	string ret;
	for (vector<string>::const_iterator iter = emts.begin(); iter != emts.end(); ++iter) {
		ret += *iter;
		if (iter + 1 != emts.end())
			ret += " ";
	}
	return ret;
}

replie_type ERR_NOSUCHNICK_401(const string& nickname) {
	return nickname + " :No such nick/channel";
}

replie_type ERR_NONICKNAMEGIVEN_431(void) {
	return ":No nickname given";
}

replie_type ERR_ERRONEUSNICKNAME_432(const string& nick) {
	return nick + " :Erroneus nickname";
}

replie_type ERR_NICKNAMEINUSE_433(const string& nick) {
	return nick + " :Nickname is already in use";
}

replie_type RPL_NAMREPLY_353(const string& channel, const vector<string>& names) {
	string ret = channel + " :";
	ret += join(names);
	return ret;
}

replie_type RPL_ENDOFNAMES_366(const string& channel) {
	return channel + " :End of /NAMES list";
}