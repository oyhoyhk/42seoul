#ifndef SERVER_SERVICE
#define SERVER_SERVICE

#include "header.hpp"
#include "Channel/ChannelManager.hpp"
#include "User/UserManager.hpp"

/*
** @brief 가능하면 모든 기능은 해당 클래스를 통해서 사용하는 것을 권장함
*/
class ServerService {
private:
    ChannelManager  _channelManager;
    UserManager     _userManager;

    ServerService operator= (const ServerService& ref);
    ServerService(const ServerService& ref);

public:

    ServerService(void);
    ~ServerService(void);

    /*
    * @param user_name: 찾고 싶은 유저 이름
    * @return User 객체의 포인터 값 (delete하면 안됨)
    * @throw 찾지 못하면 ServerService::UserNotExist를 던짐
    */
    User* getUserWithName(const string& user_name) const;
    
    /*
    * @param fd: 찾고 싶은 유저의 fd
    * @return User 객체의 포인터 값 (delete하면 안됨)
    * @throw 찾지 못하면 ServerService::UserNotExist를 던짐
    */
    User* getUserWithFD(const int& fd) const;

    /*
    * @param channel_name: 찾고 싶은 채널의 이름
    * @return Channel 객체의 포인터 값 (delete하면 안됨)
    * @throw 찾지 못하면 ServerService::ChannelNotExist를 던짐
    */
    Channel* getChannelWithName(const string& channel_name) const;

    /*
    * @param user_name: 추가할 유저의 이름
    * @param fd: 추가할 유저의 fd
    * @brief 유저를 추가하고 성공, 실패 여부를 리턴
    * @return 유저 성공 추가하면 true, 이미 존재하는 유저이름이면 false 리턴
    */
    bool addUser(const string& user_name, const int& fd);

    /*
    * @param user_name: 지우고 싶은 유저의 이름
    * @throw 만약 없는 유저를 지운다면,ServerService::UserNotExist를 던짐
    */
    void deleteUserWithName(const string& user_name);

    /*
    * @param channel_name: 들어갈 채널 이름
    * @param user_name: 들어갈 유저 이름
    * @throw 만약 없는 유저라면, ServerService::UserNotExist를 던짐
    * @brief 만약 채널이 존재하지 않는다면 새로운 채널을 만듬
    */
    void joinChannelWithUserName(const string& channel_name, const string& user_name);

    /*
    * @param channel_name: 나갈 채널 이름
    * @param user_name: 나갈 유저 이름
    * @throw 만약 없는 채널이라면 ServerService::ChannelNotExist를 던짐
    * @throw 만약 없는 유저라면 ServerService::UserNotExist를 던짐
    */
    void partChannelWithUserName(const string& channel_name, const string& user_name);

    /*
    * @param channel_name: 검색할 채널 이름
    * @throw 만약 없는 채널이라면 ServerService::ChannelNotExist를 던짐
    * @return 해당 채널에 들어있는 User객체의 포인터값들의 vector를 리턴함
    */
    vector<User*> getUsersInChannel(const string& channel_name) const;

    /*
    * @param user_name: 검색할 유저의 이름
    * @throw 만약 없는 유저라면 ServerService::UserNotExist를 던짐
    * @return 해당 유저가 들어가 있는 Channel객체의 포인터값들의 vector를 리턴함
    */
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