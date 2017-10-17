// All Right reserved: this code is written by Christian Toinard : christian.toinard(at)insa-cvl.fr
// Any usage without citation will be prosecuted in accordance with the local law.
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>

#define MY_PORT		9999 // betwenn 1024 & 49151
#define MAXBUF		1024

int main(void)
{
	int nConnectionDescriptor;
	struct sockaddr_in myExtremity;
	char buffer[MAXBUF];

  	if ( (nConnectionDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
			perror("Socket");
			exit(errno);
	}

	bzero(&myExtremity, sizeof(myExtremity));
	myExtremity.sin_family = AF_INET;
	myExtremity.sin_port = htons(MY_PORT);
	myExtremity.sin_addr.s_addr = INADDR_ANY;

  	if ( bind(nConnectionDescriptor, (struct sockaddr*)&myExtremity, sizeof(myExtremity)) != 0 )
	{
		perror("socket--bind");
		exit(errno);
	}

	if ( listen(nConnectionDescriptor, 20) != 0 )
	{
		perror("socket--listen");
		exit(errno);
	}
	
	char *tmp;
	//scanf("%s", tmp);

	int sin_size = sizeof(struct sockaddr_in);
	int nAcceptDesc;
	
	if ((nAcceptDesc = accept(nConnectionDescriptor, (struct sockaddr *)&myExtremity, &sin_size)) < 0 )
	{
		perror("accept error");
		return 1;
	} else {
		printf("Connection %d\n", nAcceptDesc);
		//printf("inet_ntoa :%d %i\n", inet_ntoa(nAcceptDesc_addr.sin_addr), ntohs(newDesc_addr.sin_port));
	}
	
	
	while( read(nAcceptDesc, buffer, MAXBUF) > 0) printf("%s\n", buffer);
	
	
    	//while (1);   
}

/*
1.1 )
	L'IETF est l'Internet Engineering Task Force, et à pour objectif de 
faire mieux fonctionner Internet en fournissant des document technique utiles
anConnectionDescriptorfin d'influencer la façon dont les gens vont designer, utiliser et gérer internet. Les port que l'on va utiliser sont les ports entre 1024 et 49151.

1.2 )
	>>telnet 127.0.0.1 9999
	La connexion est bien possible.	

1.3 )

	Argument 1 ( n_desc_res ) : numéro de descripteur du serveur
	Argument 2 ( server_addr ) : addresse du serveur
	Argument 3 ( sin_size ) : taille de l'addresse du sreveur
1.4 )
	Cette valeur correspond au uméro de descripteur du socket accepté. Ici le numéro de descritpeut est 4.

1.5 ) 
	
1.6 ) 
	inet_ntoa converti une adresse en une chaine décimale IPv4
	La taille en nombre de bits d'une adresse IPv4 est de 32 bits.	

1.7 )
	ntohs converti un entier court netshort
	Un port à une taille de 16bits


2.2 ) 
	read retourne le nombre d'octets qui sont lus

2.3 ) 
	On peut constater que le serveur affiche ce que le client lui envoie.
*/
