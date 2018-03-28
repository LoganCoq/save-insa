#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char ** argv) {
	if( argc != 2){
		printf("fonction prend 2 arguments");
		exit(EXIT_FAILURE);
	}
	char buf[BUFSIZE];
	int fd;
	int ncar;
	fd = open(argv[1], O_RDONLY);
	while( (ncar = read(fd,buf, BUFSIZE)))
	{
		write(STDOUT_FILENO, buf, ncar);
	}
	close(fd);
}
