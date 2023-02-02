#ifndef HEADER_HPP
#define HEADER_HPP

#include <cstring>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <poll.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

 
#define PORT 20162
#define BUFFER_SIZE 512
#define LISTEN_QUEUE_SIZE 5
#define MAX_FD_SIZE 5
 

std::vector<std::string>	split(char *input, std::string delimiter);
std::vector<std::string>	split(std::string str, std::string delimiter);

#endif