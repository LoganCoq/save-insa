#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUFSIZE_S 1
#define BUFSIZE_M 2048
#define BUFSIZE_L 40000

static void cp_file(const char *src, const char *dst)
{
	struct stat stsrc, stdst;
	FILE *fsrc, *fdst;
	int c;

	char buffer[BUFSIZE_S];
	//char buffer[BUFSIZE_M];
	//char buffer[BUFSIZE_L];

	lstat(src, &stsrc);
	lstat(dst, &stdst);

	if (stsrc.st_ino == stdst.st_ino && stsrc.st_dev == stdst.st_dev)
	{
		fprintf(stderr, "%s et %s sont le meme fichier\n", src, dst);
		return;

	}
	fsrc = fopen(src, "r");
	fdst = fopen(dst, "w");
	while ( c = fread( buffer, BUFSIZE_S, 1, fsrc) )
	{
		fwrite( buffer, BUFSIZE_S, 1, fdst);
	}	
	fclose(fsrc);
	fclose(fdst);
}

int main(int argc, char **argv)
{
	if ( argc < 3)
	{
		
	}
}
