#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void pr_pathconf(char *path, int name, char *message);

int main(int argc, char ** argv)
{
	char * chemin;
	chemin = (char*)malloc(256*sizeof(char));
	printf("chemin?\n");
	fgets(chemin, 255, stdin);
	chemin[strlen(chemin)-1]='\0';
	pr_pathconf(chemin ,_PC_LINK_MAX, "nb liens max");
	free(chemin);

	pr_pathconf("exo3.c", _PC_NAME_MAX, "_PC_NAME_MAX");
	pr_pathconf("exo3.c", _PC_LINK_MAX, "_PC_LINK_MAX");
	return EXIT_SUCCESS;	
}

void pr_pathconf(char *path, int name, char *message)
{
	long i;
	printf("%s\n",message);
	i = pathconf(path,name);
	if(i==-1)
	{	
		perror("error");
	}
	else {
		printf("%li\n",i);
	}
}
