#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main(const int argc, const char **argv)
{
	int sock;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0  )
	{
		perror("erreur de socket");
		return 1;
	} else {
		printf("Le socket à bien été créer. Descripteur : %d\n", sock);
	}
	
	struct sockaddr_in s_addr;

	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = INADDR_ANY;
	s_addr.sin_port = htons(APP_PORT);

	memset(&(s_addr.sin_zero), 0, 8);

	if (bind(sock, (struct sockaddr_in *) &s_addr, sizeof(s_addr)) < 0)
	{
		perror("bind error");
		return 1;
	} else {
		printf("server binded");
	}

	if (listen(sock, BACKLOG) < 0) {
		perror("listen error");
		return 1;
	} else {
		printf("Server listening\n");
	}


	return 0;
}
