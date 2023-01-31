#include "../includes/header.hpp"
#include "Server/Server.hpp"
#include <exception>

int main(int ac, char *av[]) {
	Server server;

	try {
		server.setSocket();
	} catch (std::exception &e) {
		std::cerr<<e.what()<<std::endl;
		return 1;
	}
	while (true) {
		// 클라이언트 접근 확인, poll은 다중입출력을 위해서 사용되고, 이벤트가 발생한 fd의 개수를 반환한다.
		// poll은 해당 fd에 해당 event가 발생했는지 확인해준다. 해당 event가 발생하면 실행 결과를 revent에 채워 돌려보낸다.
		// 따라서, revent를 조사해서 이후에 처리를 어떻게 할지 결정하게 된다.
		int result = poll(server.getPollFDs(), MAX_FD_SIZE, -1); // -1 : 무한 대기
		if (result == -1) {
			std::cerr << "Poll Error Occured..." <<std::endl;
			return 1;
		}

		if (result > 0) {
			server.addPollFD();
			server.sendResponse();
		}
	}
	server.closeListenFD();
	return 0;
}