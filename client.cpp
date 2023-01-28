#include "includes/header.hpp"
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage : " << argv[0] << " IPv4-address" << std::endl;
		return -1;
	}
	struct sockaddr_in connectSocket;

	memset(&connectSocket, 0, sizeof(connectSocket));

	connectSocket.sin_family = AF_INET;
	inet_aton(argv[1], (struct in_addr*) &connectSocket.sin_addr.s_addr);
	connectSocket.sin_port = htons(PORT);

	int connectFD = socket(AF_INET, SOCK_STREAM, 0);
	printf("connectFD : [%d]\n", connectFD);

	if (connect(connectFD, (struct sockaddr*) &connectSocket, sizeof(connectSocket)) == -1) {
		printf("Can not connect.\n");
		return -1;
	}
	else {
		int readBytes, writtenBytes;
		char sendBuffer[BUFFER_SIZE];
		char receiveBuffer[BUFFER_SIZE];
		while (true) {
			printf("input :: ");
			fgets(sendBuffer, BUFFER_SIZE, stdin);
			printf("sendBuffer : [%s], length : [%zu]\n", sendBuffer, strlen(sendBuffer));
			write(connectFD, sendBuffer, strlen(sendBuffer));
			readBytes = read(connectFD, receiveBuffer, BUFFER_SIZE);
			receiveBuffer[readBytes] = '\0';
			printf("%d bytes read\n", readBytes);

			fputs(receiveBuffer, stdout);
			fflush(stdout);
		}
	}
	close(connectFD);
	return 0;
}