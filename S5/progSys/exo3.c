#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char ** argv)
{
	char * erreur;
	//syscall ( num AS, num descrpt sortie, chaine, taille)
	if (syscall(SYS_write, STDOUT_FILENO, "hello\n", 6)< 0)
	// pour faire planter
	//if (syscall(SYS_write, 3, "hello\n", 6)<0)
	{
		erreur = strerror(errno);
		printf("Mon erreur : %s\n", erreur);
		//perror("syscall"); // erreur du dernier appel système
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
