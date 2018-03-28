#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFSIZE_S 1
#define BUFSIZE_M 2048
#define BUFSIZE_L 40000

static void cp_file(const char *src, const char *dst)
{
	int fdsrc, fddst;
	//char buffer[BUFSIZE_S];
	//char buffer[BUFSIZE_M];
	char buffer[BUFSIZE_L];
	int nchar;
	fdsrc = open(src, O_RDONLY);
	fddst = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0666);

	//while (( nchar = read(fdsrc, buffer, BUFSIZE_S)))
	//while (( nchar = read(fdsrc, buffer, BUFSIZE_M)))
	while (( nchar = read(fdsrc, buffer, BUFSIZE_L)))
	{
		write(fddst, buffer, nchar);
	}
	close(fdsrc);
	close(fddst);
}

int main(int argc, char ** argv)
{
	if ( argc < 3 )
	{
		printf("Wrong usage of cmd. Usage ./cp_AS src dst");
		exit(EXIT_FAILURE);
	}
	else
	{
		cp_file(argv[1], argv[2]);
		exit(EXIT_SUCCESS);
	}
}
