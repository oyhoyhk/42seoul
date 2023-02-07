#include "Command.hpp"
#include "Utils.hpp"

void Command::_handleJOIN(Server &server, int fd, const string &msg) {
    vector<string>  msgChannel = split(msg, " ");
    vector<string> channels = split(msgChannel[1], ",");

    for (vector<string>::iterator ch = channels.begin(); ch != channels.end(); ++ch) {
        const string&   channelName = *ch;
        Channel*        channel = NULL;
        User*           user = NULL;

        // 모든 채널에서 이름으로 조회해서 없으면
        user = _service.getUserWithFD(fd);
        channel = _service.joinChannelWithUserName(channelName, user->getName());

        string joinMessage = ":" + user->getName() + "!" + user->getId() + "@" + user->getHostname() + " JOIN :" + channel->getName() + "\r\n";
        string nameReply   = ":irc.local 353 " + user->getName() + " = " + channel->getName() + " :@";
        
        vector<User *> list = channel->getUsers();
        vector<User *>::iterator it;
        for (it = list.begin(); it != list.end(); ++it) {
            nameReply += (*it)->getName() + " ";
        }
        nameReply += "\r\n";
        string endOfNames   = ":irc.local 366 " + user->getName() + " " + channel->getName() + " :End of /NAMES list.\r\n";

        sendMessage(fd, joinMessage);
        sendMessage(fd, nameReply);
        sendMessage(fd, endOfNames);

        string response = ":" + user->getName() + "!" + user->getId() + "@" + user->getHostname() + " JOIN :" + channelName + "\r\n";

        for(it = list.begin();it != list.end(); ++it) {
            if ((*it)->getFD() != fd) {
                cout << "[JOIN RESPONSE] " << _service.getUserWithFD((*it)->getFD())->getName() << " >> " << response << endl;
                sendMessage((*it)->getFD(), response);
            }
        }
    }
}