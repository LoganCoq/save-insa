/**/
#include <rpc/rpc.h>
#include <signal.h>
/**/
#include <stdio.h>
#include <ctype.h>

#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

/**/
#include "rdict.h"

#define	RMACHINE	"dell"
#define	PROTOCOL	"udp"
CLIENT	*handle;
/**/

#include "CodeClient.hc"

/**/
/*void Rupture()
{
        printf("Rupture connexion\n");
	signal(SIGPIPE,Rupture);
	handle=0;
	while (handle==0)
	{
	handle = clnt_create(RMACHINE, RDICTPROG, RDICTVERS, PROTOCOL);
		printf("Impossible contacter programme distant\n");
		sleep(1);
	};
}

**/
int
main(argc,argv)
int argc;
char *argv[];
{

	/**/
//	signal(SIGPIPE,Rupture);

	struct sockaddr_in server;
	struct hostent *remote_host;
	int sock = RPC_ANYSOCK;
	int sendsz = 0;
	int recvsz = 0;
	server.sin_family = AF_INET;
	if((remote_host = gethostbyname(argv[1])) == (struct hostent *)NULL)
	{
		fprintf(stderr, "%s:unknown host:%s\n", argv[0], argv[1]);
		exit(__LINE__);
	}
	(void) memcpy( (char *) &server.sin_addr, (char *)remote_host->h_addr, (size_t) remote_host->h_length);
	server.sin_port = htons(atoi(argv[2]));
	printf("Avant clnttcp_create\n");

	handle = clnttcp_create(&server, RDICTPROG, RDICTVERS, &sock, sendsz, recvsz);
	

	if (handle==0) {
		printf("Impossible contacter programme distant\n");
		exit(1);
	};
	/**/

	while (!fonctionClient())
        {
                replay=1;
//		Rupture();
        };

}
