#include "Command.hpp"
#include "Utils.hpp"
#include "ReplieFactory.hpp"

void Command::_handleKICK(Server &server, int fd, const string &msg) {
	vector<string> words = split(msg, " ");
	string channelName = words[1];	// TODO: 예외처리
	string targetName = words[2];	// TODO: 예외처리
	string comment = "";
	if (words.size() > 3) {
		comment += words[3];
	}

	User *user = _service.getUserWithFD(fd);
	// channel의 operator인지 확인
	Channel *channel = _service.getChannelWithName(words[1]);
	if (!channel->isOperator(user)) {
		// :irc.local 482 yubchoi #t2 :You must be a channel operator
		sendMessage(fd, ERR_CHANOPRIVSNEEDED_482(user->getName(), channelName));
		return ;
	}

	// TODO: channelName이 존재하는지 확인
	// TODO: targetName이 존재하는지 확인

	vector<User*> users = channel->getUsers();
	// :yubin!root@127.0.0.1 KICK #t2 yubchoi :hi
	string response = ":" + user->getName() + "!" + user->getId() + "@" + user->getHostname() + " KICK " + channelName + " " + targetName + " :" + comment + "\r\n";
	for (vector<User*>::iterator iter = users.begin(); iter != users.end(); ++iter) {
		sendMessage((*iter)->getFD(), response);
	}
	_service.partChannelWithUserName(channelName, targetName);
}