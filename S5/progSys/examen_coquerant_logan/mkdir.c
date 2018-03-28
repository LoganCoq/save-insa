#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char ** argv) {

	if( argc != 2 )
	{
		printf("wrong usage\n");
		return EXIT_FAILURE;
	}
	
	if( (mkdir(argv[1], S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)) == -1)
	{
		perror("creation rep");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;

}
