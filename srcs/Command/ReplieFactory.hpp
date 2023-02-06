#ifndef REPLIEFACTORY_HPP
#define REPLIEFACTORY_HPP

#include "header.hpp"

typedef const string replie_type;
inline replie_type ERR_NOSUCHNICK_401(const string& nickname);
inline replie_type ERR_NONICKNAMEGIVEN_431(void);
inline replie_type ERR_ERRONEUSNICKNAME_432(const string& nick);
inline replie_type ERR_NICKNAMEINUSE_433(const string& nick);
inline replie_type RPL_NAMREPLY_353(const string& channel, const vector<string>& names);
inline replie_type RPL_ENDOFNAMES_366(const string& channel);
#endif 