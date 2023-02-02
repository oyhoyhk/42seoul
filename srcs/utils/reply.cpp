#include <iostream>

std::string ERR_NONICKNAMEGIVEN(void) {
	return ":No nickname given" ;
}

std::string ERR_ERRONEUSNICKNAME(void) {
	return " :Erroneus nickname";
}

std::string ERR_NICKNAMEINUSE(void) {
	return " :Nickname is already in use";
}

std::string ERR_NICKCOLLISION(void) {
	return " :Nickname collision KILL";
}