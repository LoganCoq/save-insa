#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

// Processus zombi
// Le danger avec ce tyoe de processus est que l'on ne peut pas le kill.

int main(int argc, char ** argv)
{
	int pid = fork();
	int status;
	if ( pid > 0 ){
		// code pere
		printf("pere %d\n", getpid());
		printf("fils %d\n", pid);
		sleep(30);
		wait(&status);
	} else {
		// code fils
		printf("fils %d\n", getpid());
		printf("pere %d\n", getppid());	
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
}
