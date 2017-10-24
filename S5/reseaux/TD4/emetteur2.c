// All Right reserved: this code is written by Christian Toinard : christian.toinard(at)insa-cvl.fr
// Any usage without citation will be prosecuted in accordance with the local law.
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#define BUFFERSIZE 1024

typedef void (*sighandler_t)(int);

void catch(void)
{
	exit(EXIT_SUCCESS);
}

int main(int argc, const char *argv[])
{
    signal(SIGINT,(sighandler_t)catch);

    if (argc != 2)
    {
        printf("Error argv");
	exit(EXIT_FAILURE);
    }

	int sdemande;
	if((sdemande = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket()");
		exit(EXIT_FAILURE);
	}

	int on = 1;
	if(setsockopt(sdemande, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) < 0)
	{
		perror("setsockopt()");
		exit(EXIT_FAILURE);
	}

    struct sockaddr_in dst;
    dst.sin_addr.s_addr = inet_addr(argv[1]);
    dst.sin_family = AF_INET;
    dst.sin_port   = htons(5011);

    sendto(sdemande, "Bonjour", 7, 0, (struct sockaddr*)&dst, sizeof(dst));
}
