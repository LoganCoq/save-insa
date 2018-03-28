#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char ** argv) {

	if ( argc == 1 )
	{
		printf("pas assez d'arguments\n");
		return EXIT_FAILURE;
	}
	int i;
	for(i=1; i<argc; i++)
	{
		printf("%s ", argv[i]);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
