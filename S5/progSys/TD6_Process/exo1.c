#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
	int pid = fork(); //A partir d'ici un deuxième processus se lance et continue l'execution
	if ( pid > 0 ) {
		printf("P1 pere pid : %d\n", getpid());
		printf("P1 fils pid : %d\n", pid);
	} else if ( pid == 0 ){
		printf("P2 fils pid : %d\n", getpid());
	}
	
	exit(EXIT_SUCCESS);
}
