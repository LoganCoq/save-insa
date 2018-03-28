// ------------------------------------------------------------------
// exemple-signal-3.c
// Fichier d'exemple du livre "Developpement Systeme sous Linux"
// (C) 2000-2010 - Christophe BLAESS -Christophe.Blaess@Logilin.fr
// http://www.logilin.fr
// ------------------------------------------------------------------
// #define	_XOPEN_SOURCE
// #define	_GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int i;

void gestionnaire (int numero)
{
	int compteur;
	compteur++;
	signal(numero, gestionnaire);  //installe un gestionnaire de signal
				       // en POSIX, l'instalation est "ONESHOT", on est obliger de réinstaller le gestionnaire
	fprintf(stdout, "debut du gestionnaire de signal %d\n", numero);
	for (i = 1; i < 4; i ++) {
		fprintf(stdout, "%d\n", i);
		sleep(1);
	}
	fprintf(stdout, "fin du gestionnaire de signal %d\n", numero);
}

int main (void)
{
	signal(SIGUSR1, gestionnaire); // function called if SIGUSR1 received
	//signal(SIGCHLD, gestionnaire);
	
	if (fork() == 0) {
		kill(getppid(), SIGUSR1);
		sleep(1);
		kill(getppid(), SIGUSR1);
		sleep(1);
		kill(getppid(), SIGUSR1); // on ne garde pas en mémoire ce signal car on ne conserve pas
					  // le nombre de fois que l'on a reçut le signal
					  //  ( signal non empilable )
		while(1) 
			pause();
	} else {
		while (1)
			pause();
	}
	return EXIT_SUCCESS;
}

