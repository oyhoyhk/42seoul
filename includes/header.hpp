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
#include <stdexcept>

using namespace std;

#define PORT 20162
#define BUFFER_SIZE 512
#define LISTEN_QUEUE_SIZE 5
#define MAX_FD_SIZE 5
#define MAX_USER_SIZE MAX_FD_SIZE
#define MAX_CHANNEL_SIZE 5


// vector<string>	split(const string& str, const string& delimiter);

#endif
