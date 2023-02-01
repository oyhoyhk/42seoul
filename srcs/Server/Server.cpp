#include "Server/Server.hpp"
#include "header.hpp"

static bool isAllNumber(const std::string& str) {
	for (size_t i = 0; i < str.length(); ++i)
		if (!std::isdigit(str[i])) return false;
	return true;
}

Server::Server(const std::string& port, const std::string& password) {
	if (port.length() > 5 || !isAllNumber(port)
		|| (_port = std::atoi(port.c_str())) > 65535)
		throw InitServerException();
	_password = password;
	_setFunctions();
}

Server::~Server() {
	close(_socket);
}

void	Server::prepare(void) {
	int opt = 1;
	memset(&_sockaddr, 0, sizeof(_sockaddr));
	_sockaddr.sin_family = AF_INET;
	_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	_sockaddr.sin_port = htons(_port);

	if ((_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1
		|| setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1
		|| bind(_socket, (struct sockaddr*)&_sockaddr, sizeof(_sockaddr)) == -1
		|| listen(_socket, LISTEN_QUEUE_SIZE) == -1) {
		close(_socket);
		throw InitServerException();
	}
	_pollFDs[0].fd = _socket;
	_pollFDs[0].events = POLLIN;
	_pollFDs[0].revents = 0;
	for (int i = 1; i < MAX_FD_SIZE; ++i) _pollFDs[i].fd = -1;
}

void	Server::start(void) {
	int result;
	while (true) {
		result = poll(_pollFDs, MAX_FD_SIZE, -1);
		if (result > 0) {
			_acceptConnections();
			_sendResponse();
		}
	}
}

void	Server::_acceptConnections(void) {
	struct sockaddr_in	addr;
	socklen_t			addrSize;

	if (_pollFDs[0].revents != POLLIN) return;
	int	connectFD = accept(_socket, (struct sockaddr *)&addr, &addrSize);
	for (int i=1; i<MAX_FD_SIZE; ++i) {
		if (_pollFDs[i].fd == -1) {
			_pollFDs[i].fd = connectFD;
			_pollFDs[i].events = POLLIN;
			_pollFDs[i].revents = 0;
			break ;
		}
	}
}

void	Server::_sendResponse(void) {
	ssize_t	length;
	char	buf[BUFFER_SIZE+ 1];
	std::vector<std::string> list;
	std::vector<std::string>::iterator iter;

	std::vector<std::string> words;
	std::vector<std::string>::iterator iter2;
	for (int i = 1; i < MAX_FD_SIZE; ++i) {
		switch (_pollFDs[i].revents) {
			case 0 : //no events
				break ;
			case POLLIN : //data is ready
				length = recv(_pollFDs[i].fd, buf, BUFFER_SIZE, 0);
				buf[length] = '\0';
 				list = split(buf, "\n");

				for(iter = list.begin(); iter != list.end(); ++iter) {
					std::cout << "input : [" << *iter <<"]"<<std::endl;
					words = split(*iter, " ");
					for (iter2 = words.begin(); iter2 != words.end(); ++iter2) {
						std::cout << "word : [" << *iter2 << "]" <<std::endl;
					}
				}

				printf("%lu bytes read\n", length);
				printf("[%s]", buf);
				for (int j = 1; j < MAX_FD_SIZE; ++j) {
					if (_pollFDs[j].fd != -1 && _pollFDs[i].fd != _pollFDs[j].fd) {
						write(_pollFDs[j].fd, buf, strlen(buf));
					}
				}
				break ;
			default :
				close(_pollFDs[i].fd);
				_pollFDs[i].fd = -1;
				_pollFDs->revents = 0;
		}
	}
}

const char* Server::InitServerException::what(void) const throw() {
	return "Initiating Server Failed...";
}

void Server::_setFunctions(void) {
	_funcMap["CAP"]			= &Server::handleCAP;
	_funcMap["NICK"] 		= &Server::handleNICK;
	_funcMap["PRIVMSG"]		= &Server::handlePRIVMSG;
	_funcMap["LIST"]		= &Server::handleLIST;
	_funcMap["INVITE"]		= &Server::handleINVITE;
	_funcMap["KICK"]		= &Server::handleKICK;
	_funcMap["PING"]		= &Server::handlePING;
	_funcMap["JOIN"]		= &Server::handleJOIN;
	_funcMap["QUIT"]		= &Server::handleQUIT;
	_funcMap["PART"]		= &Server::handlePART;
	_funcMap["NOTICE"]		= &Server::handleNOTICE;
	_funcMap["PASS"]		= &Server::handlePASS;
	_funcMap["USER"]		= &Server::handleUSER;
}