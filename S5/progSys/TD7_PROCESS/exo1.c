#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Les processus orphelins sont généralement utilisés pour les programmes deamon 
// , les processus systemes qui doivent s'executés en fond
int main(int argc, char ** argv)
{
	int pid = fork();
	
	if ( pid > 0 ){
		// code pere
		printf("pere %d\n", getpid());
	} else {
		// code fils
		printf("fils %d\n", getpid());
		sleep(3);
		printf("fils %d\n", getpid());
		printf("pere %d\n", getppid());	
	}
	exit(EXIT_SUCCESS);
}
