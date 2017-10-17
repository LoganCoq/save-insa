// All Right reserved: this code is written by Christian Toinard : christian.toinard(at)insa-cvl.fr
// Any usage without citation will be prosecuted in accordance with the local law.
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define MY_PORT 9998
#define MAXBUF	1024


int main(int argc, const char *argv[])
{
	int connectionDescriptor;
	if((connectionDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket()");
		exit(errno);
	}

	struct sockaddr_in self;
	bzero(&self, sizeof(self));
	self.sin_family      = AF_INET;
	self.sin_port        = htons(MY_PORT);
	self.sin_addr.s_addr = INADDR_ANY;

	if(bind(connectionDescriptor, (struct sockaddr*)&self, sizeof(self)) != 0)
	{
		perror("bind()");
		exit(errno);
	}

	if(listen(connectionDescriptor, 20) != 0)
	{
		perror("listen()");
		exit(errno);
	}

	printf("Father [%d]\n", getpid());

	char buffer[MAXBUF];
	pid_t client[5];
	int nbclient = 0;
	ssize_t sizereceveid;

	while(1)
	{
		struct sockaddr_in client_addr;
		socklen_t addrlen = sizeof(client_addr);

		int nClientConnection = accept(connectionDescriptor, (struct sockaddr*)&client_addr, &addrlen);

		printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

		switch((client[nbclient] = fork()))
		{
			case -1:
				perror("fork()");
				exit(EXIT_FAILURE);

			case 0:
				close(connectionDescriptor);
				printf("Child [%d]\n", getpid());

				while(1)
				{
					int nbs = write(nClientConnection, buffer, read(nClientConnection, buffer, MAXBUF));
/* TO BE COMPLETED: send back the received buffer in a single C instruction */
					printf("[%d] : \n", getpid());

					write(1, buffer, nbs); /* Why write on descriptor number 1 ? (Is it because it is the best one ?)*/

					if(nbs == 0)
					{
						close(nClientConnection);
						printf("The end of [%d]: \n", getpid());
						exit(1);
					}

					if(strcmp(buffer, "/exit\r\n") == 0)
					{
						close(nClientConnection);
						exit(0);
					}
				}

			default:
				nbclient++;
				close(nClientConnection);
				break;
		}
	}


}

/*

1.1)
:%s/sockfd/connectionDescriptor/g
:%s/clientfd/nClientConnection/g
On fait cela pour que les descripteur soient plus clairs

1.2)
ligne 69 : on ferme connectionDescriptor 
ligne 81 : on ferme la connection si le buffer reçu est vide
ligne 88 : on ferme la connection si le buffer contient l'instruction exit
ligne 95 : on ferme la connexion du client si la connexion n'a pas réussie

1.3)

1.4)
On écrit dans le descripteur 1 car cela correspond à la sortie standard (stdout) afin d'afficher à l'écran le buffer.

1.5)
telnel 127.0.0.1 9998


*/
