#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

// join
std::string	join(std::vector<std::string> vec);

// split
std::vector<std::string>	split(const std::string& str, const std::string& delimiter);

// reply
std::string ERR_NONICKNAMEGIVEN(void);
std::string ERR_ERRONEUSNICKNAME(void);
std::string ERR_NICKNAMEINUSE(void);
std::string ERR_NICKCOLLISION(void);

#endif