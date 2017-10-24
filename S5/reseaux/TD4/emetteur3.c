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
#include <string.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#define BUFFERSIZE 1024

typedef void (*sighandler_t)(int);

void catch(void)
{
	exit(EXIT_SUCCESS);
}

int main()
{
	signal(SIGINT,(sighandler_t)catch);

    //Question 3.1
	char liste[BUFFERSIZE];
	struct ifconf ifc;
	ifc.ifc_len = sizeof(liste);
	ifc.ifc_buf = liste;
  
    //Question 3.2
	
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

	//Question 3.4
	if ((ioctl(sdemande ,SIOCGIFCONF, (char*)&ifc))<0)
	{
		perror("ioctl()");
		exit(EXIT_FAILURE);
	}

	//Question 3.7
	struct ifreq *ifr;
	ifr = ifc.ifc_req;

	//Question 3.8
	int n = ifc.ifc_len/sizeof(*ifr);
	for(; --n >= 0; ifr++) {
	//Question 3.9
		if((ioctl(sdemande, SIOCGIFCONF,(char *) ifr))<0)
		{
			perror("ioctl()");
			continue;	
		}

        //Question 3.10

        //Question 3.11
 	       struct sockaddr_in dst;
       		bcopy(&ifr->ifr_broadaddr, &dst, sizeof(ifr->ifr_broadaddr));
        	dst.sin_family = AF_INET;
        	dst.sin_port = htons(5011);
        //Question 3.12
        	sendto(sdemande, "Bonjour", 7, 0,(struct sockaddr*)&dst, sizeof(dst));
	}
	return 0;
}

/*
========
1.1)
La diffusion sur une adresse broadcast permet a tout les connexion sous le même masque de sous-réseau d'intercepter les informations. Par exemple, si l'adresse de broadcast est 192.168.1.255, toutes les adresses de 192.168.1.1 à 192.168.1.254 pourront recevoir les données.
On peut comparer une adresse de broadcast car sur un reseau local ff:ff:ff:ff:ff:ff est l'adresse de diffusion générale, comme une adresse de broadcast telle que 192.168.1.255 par exemple.

1.2)
eth1 : 172.31.1.255
vmnet1 : 172.16.190.255
vmnet8 : 172.16.162.255

1.3)

1.4)
On peut voir sur le recepteur que l'on recoit le message envoyer par l'emetteur, mais aussi par l'ensemble des emetteur des personnes sur le réseau

=========
2.1)
ifc peut bien contenir un tableau de struct ifreq car union permet d'allouer soit un char* soit un struct ifreq*

2.2)

2.3)
setsockopt permet d'affecter des options au socket, ici on le met en mode broadcast

2.4)

2.5)
On peut espérer avoir 4 interfaces

2.6)
En divisant la taille de l'ensemble des interfaces par la taille de la liste des interfaces on obtient le nombres d'interfaces.

2.7)

2.8)


3.1)


*/
