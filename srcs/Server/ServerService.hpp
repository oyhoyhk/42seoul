#ifndef SERVER_SERVICE
#define SERVER_SERVICE

#include "header.hpp"
#include "Channel/ChannelManager.hpp"
#include "User/UserManager.hpp"

class ServerService {
private:
    ChannelManager  _channelManager;
    UserManager     _userManager;

    ServerService operator= (const ServerService& ref);
    ServerService(const ServerService& ref);

public:

    ServerService(void);
    ~ServerService(void);

    User* getUserWithName(const string& user_name) const;
    User* getUserWithFD(const int& fd) const;
    Channel* getChannelWithName(const string& channel_name) const;
    void addUser(const string& user_name, const int& fd);
    void deleteUserWithName(const string& user_name);
    void joinChannelWithUserName(const string& channel_name, const string& user_name);
    void partChannelWithUserName(const string& channel_name, const string& user_name);
    vector<User*> getUsersInChannel(const string& channel_name) const;
    vector<Channel*> getChannelsFromUser(const string& user_name) const;

    class UserNotExist: public exception {
    public:
        const char* what() const throw();
    };

    class ChannelNotExist: public exception {
    public:
        const char* what() const throw();
    };
};

#endif