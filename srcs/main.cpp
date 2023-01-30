#include "../includes/header.hpp"
#include "Server/Server.hpp"
#include <exception>

int main() {
	Server server;

	try {
		server.setSocket();
	} catch (std::exception &e) {
		std::cerr<<e.what()<<std::endl;
		return 1;
	}
	while (true) {
		int result = poll(server.getPollFDs(), MAX_FD_SIZE, -1); // -1 : 무한 대기
		//if (result == -1) {
		//	std::cerr << "Poll Error Occured..." <<std::endl;
		//	return 1;
		//}
		if (result > 0) {
			server.addPollFD();
			server.sendResponse();
		}
	}
	server.closeListenFD();
	return 0;
}