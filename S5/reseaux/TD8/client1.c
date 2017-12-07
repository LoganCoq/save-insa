

#include <stdlib.h>

#include <sys/fcntl.h>              
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
#include <string.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>


#define SERVER_PORT 12345
#define BUF_SIZE 4096

int main(int argc, char ** argv)
{
	int c, s, bytes;
	char buf[BUF_SIZE];
	struct hostent *h;
	struct sockaddr_in channel;

	if (argc != 3)
	{
		perror("Usage: client server-name file-name");
		exit(EXIT_FAILURE);
	}

	if ( !(h = gethostbyname(argv[1])))
	{
		perror("gethostbyname :");
		exit(EXIT_FAILURE);
	}

	if ((s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	memset(&channel, 0, sizeof(channel));
	memcpy(&channel.sin_addr.s_addr, h->h_addr, h->h_length);
	channel.sin_port = htons(SERVER_PORT);

	if ((c=connect(s, (struct sockaddr *) &channel, sizeof(channel))) < 0)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}

	write(s, argv[2], strlen(argv[2])+1);

	while(1)
	{
		bytes = read(s, buf, BUF_SIZE);
		if( bytes <= 0) exit(0);
		write(1, buf, bytes);
	}	
}
