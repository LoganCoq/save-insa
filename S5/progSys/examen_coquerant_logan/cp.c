#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 2048

int main(int argc, char ** argv) {

	if (argc != 3){
		printf("cp prend deux arguments \n");
		return EXIT_FAILURE;
	}

	char buf[BUFSIZE];
	int fdin, fdout;
	int ncar;

	fdin = open(argv[1], O_RDONLY);
	fdout = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC);

	while ((ncar = read(fdin, buf, BUFSIZE)))
	{
		write(fdout, buf, ncar);
	}
	close(fdin);
	close(fdout);

	return EXIT_FAILURE;
}
