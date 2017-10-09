#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv)
{

	#ifdef _POSIX_SOURCE
	printf("_POSIX_SOURCE=%d\n", _POSIX_SOURCE);
	#endif

	#ifdef _POSIX_C_SOURCE
	printf("_POSIX_C_SOURCE=%ld\n", _POSIX_C_SOURCE);
	#endif

	#ifdef _XOPEN_SOURCE
	printf("_XOPEN_SOURCE=%d\n", _XOPEN_SOURCE);
	#endif

	#ifdef _XOPEN_SOURCE_EXTENDED
	printf("_XOPEN_SOURCE_EXTENDED=%d\n", _XOPEN_SOURCE_EXTENDED);
	#endif

	#ifdef _XOPEN_VERSION
	printf("_XOPEN_VERSION=%d\n", _XOPEN_VERSION);
	#endif
		
	if (_POSIX_C_SOURCE == 200809)
		printf("Code de 2008 inclu !\n");
	else
		printf("Code par default\n");
	
	// EX4
	printf("%ld\n",sysconf(_SC_LOGIN_NAME_MAX));

	return 0;
}

// EX 2 : Il faut compiler avec gcc puis lancer le fichier binaire
// EX 3 : Les ifdef sont réalisés à la compilation et le reste à l'execution

