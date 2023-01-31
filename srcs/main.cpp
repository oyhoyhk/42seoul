#include "header.hpp"
#include "Server/Server.hpp"
#include <exception>

int main(int argc, char *argv[]) {
	try {
		if (argc != 3) throw std::runtime_error("arguments error");
		Server server(argv[1], argv[2]);
		server.prepare();
		server.start();
		return 0;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
}
