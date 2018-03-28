#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char ** argv) {

	int mod;
	if(argc != 2){
		printf("la fonction prend 1 argument : chmod fic");
		return EXIT_FAILURE;
	}
	scanf("%d", &mod);
	chmod(argv[1], mod);

	return EXIT_SUCCESS;
}
