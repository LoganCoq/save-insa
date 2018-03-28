#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
	int pid = fork();
	int status;
	if ( pid == 0 ){
		sleep(2);
		printf("fin fils\n");
		exit(EXIT_SUCCESS);
	} else if ( pid > 0 ) {
		printf("pere");
		wait(&status);
		if ( WIFEXITED(status) ){
			printf("code : %d\n", WIFEXITED(status) );
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_SUCCESS);
}
