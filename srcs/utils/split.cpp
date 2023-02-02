#include <iostream>
#include <sstream>
#include <vector>


std::vector<std::string>	split(char *input, std::string delimiter) {
 	std::vector<std::string> ret;
	std::string str(input);

    size_t pos = 0;
    std::string token;
	while (pos != std::string::npos)
    {
        pos = str.find(delimiter);

        // delimiter를 못찾으면 텍스트 끝까지 token으로 취급
        if (pos == std::string::npos)
            token = str;
        else
            token = str.substr(0, pos);

        if (token[token.size() -1] == '\r')
            token = token.substr(0, token.size() -1);
		if (token.length() == 0)
			break ;
        ret.push_back(token);
        str.erase(0, pos + delimiter.length());
    } 
    return ret;
}

std::vector<std::string>	split(std::string str, std::string delimiter) {
 	std::vector<std::string> ret;

    size_t pos = 0;
    std::string token;
	while (pos != std::string::npos)
    {
        pos = str.find(delimiter);

        // delimiter를 못찾으면 텍스트 끝까지 token으로 취급
        if (pos == std::string::npos)
            token = str;
        else
            token = str.substr(0, pos);

        if (token[token.size() -1] == '\r')
            token = token.substr(0, token.size() -1);
		if (token.length() == 0)
			break ;
        ret.push_back(token);
        str.erase(0, pos + delimiter.length());
    } 

    return ret;
}