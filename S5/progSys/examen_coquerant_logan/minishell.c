#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define BUFFER 512

// passer a 1 pour obtenir des informations de DEBUG
int DEBUG = 0;

// on stocke le ficheir de destination pour le > dans la variable fdest
char * fdest = NULL;

/*
 * Lit une commande sur l'entrée standard
 * command : la commande (chemin absolu) a exécuter
 * arg : ses arguments
 */ 
int read_command(char* command, char* arg[]){
	int cpta=1;
	int c;
	char * chaine;
	char tmp[BUFFER];
	// lire la command
	scanf("%s",command);
	if (strcmp(command,"exit")==0) {
		return -1;
	} else if (strcmp(command, "cd") ==0) {
		chdir(arg[1]);
	} else if (strcmp(command,"pwd") == 0) {
		getcwd(chaine, BUFFER);
		printf("%s \n", chaine);
	} else if (strcmp(command, "env") ==0) {
		getenv(chaine);
		printf("%s \n", chaine);
	} 
	else {
	
		//lire les arguments
		while((c=getchar())!='\n') {
			chaine=malloc((BUFFER-1) * sizeof(char));
			scanf("%s",chaine);
			if (strcmp(chaine,">")==0) {
				//lire le fichier de sortie et le stocker dans fdest
				scanf("%s",tmp);
				fdest=malloc(strlen(tmp)*sizeof(char));
				strncpy(fdest,tmp,strlen(tmp)*sizeof(char));
			}
			else{
				arg[cpta++]=chaine;
			}
		}
		arg[cpta]=NULL;
		//on retourne le nombre d'arguments
		return cpta;
	}
	return 0;
}

/*
 * Execute une commande dans un processus fils
 * command : la commande (chemin absolu) a exécuter
 * arg : ses arguments
 */
int run_command(char * command, char * arg[]) {
	pid_t status;
	int fd;
	status = fork();
	switch (status) {
		case -1:
			perror("Creation processus");
			exit(EXIT_FAILURE);
		case 0:
			// fichier de sortie ?
			if(fdest) {
				fd=open(fdest, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				if(fd==-1) {
					perror("Erreur : ");
					exit(EXIT_FAILURE);
				}
				dup2(fd, STDOUT_FILENO);
			}
			//utilisation de execv pour exécuter la commande
			if(execv(command,arg)==-1) {
				perror("Erreur : ");
				exit(EXIT_FAILURE);
			}
			if(fdest) {
				close(fd);
			}
			exit(EXIT_SUCCESS);
			break;
		default:
			//attente de la fin de la commande
			wait(&status);
			if (WIFEXITED(status)) 
				return EXIT_SUCCESS;
			return EXIT_FAILURE;

	}

}

/*
 * Mini interpreteur de commande
 * Lit une commande avec la fonction read_command
 * execute la commande avec run_command
 */
int main(int argc, char ** argv) {
	char command[BUFFER];
	char* arg[BUFFER];
	int nb_args,i;
	if(argc > 1)
		DEBUG=1;
	while(1) {
		// on initialise les variables globales	
		fdest = NULL;
		//on récupère une commande a exécuter
		printf("minishell $");
		nb_args=read_command(command, arg);
		arg[0]=command;
		//si la commande correspond a exit, on quitte
		if(nb_args==-1) {
			printf("Exit\n");
			exit(EXIT_SUCCESS);
		}

		if(DEBUG) {
			printf(" ===>commande a exécuter: %s, %d arguments [",command,nb_args);
			for(i=0; i<nb_args; i++)
				printf("%s , ",arg[i]);
			printf("], fdest : %s\n",fdest);
		}
		//on execute la commande
		if(run_command(command,arg)){
			if(DEBUG) printf("===> commande executée avec erreur\n");
		}else{
			if(DEBUG) printf("===> commande executée sans erreur\n");
		}
	}
	return EXIT_SUCCESS;
}


