#include "ServerService.hpp"

ServerService ServerService::operator= (const ServerService& ref) { }
ServerService::ServerService(const ServerService& ref) {}
ServerService::ServerService(void){}
ServerService::~ServerService(void){}

User* ServerService::getUserWithName(const string& user_name) const {
    User* user = _userManager.getUserWithName(user_name);
    if (user == NULL) throw UserNotExist();
    return user;
}

Channel* ServerService::getChannelWithName(const string& channel_name) const {
    Channel* channel = _channelManager.getChannelWithName(channel_name);
    if (channel == NULL) throw ChannelNotExist();
    return channel;
}

void ServerService::addUser(const string& name, const int& fd) {
    _userManager.addUser(name, fd);
}

void ServerService::deleteUserWithName(const string& name) {
    User* user = getUserWithName(name);
    vector<string> channelNames = user->getChannelNames();
    _channelManager.partUserFromChannels(name, channelNames);
    _userManager.deleteUser(name);
}

void ServerService::joinChannelWithUserName(const string& channel_name, const string& user_name) {
    Channel* channel = getChannelWithName(channel_name);
    User* user = getUserWithName(user_name);
    user->joinChannel(channel);
    channel->addUser(user);
}

void ServerService::partChannelWithUserName(const string& channel_name, const string& user_name) {
    Channel* channel = getChannelWithName(channel_name);
    User* user = getUserWithName(user_name);
    user->partChannel(channel);
    channel->deleteUser(user);
}

vector<User*> ServerService::getUsersInChannel(const string& channel_name) const {
    Channel* channel = getChannelWithName(channel_name);
    vector<User*> ret = channel->getUsers();
    return ret;
}

vector<Channel*> ServerService::getChannelsFromUser(const string& user_name) const {
    User* user = getUserWithName(user_name);
    vector<Channel*> ret = user->getChannels();
    return ret;
}

const char* ServerService::UserNotExist::what(void) const throw() {
    return "user not exist!";
}

const char* ServerService::ChannelNotExist::what(void) const throw() {
    return "channel not exist!";
}