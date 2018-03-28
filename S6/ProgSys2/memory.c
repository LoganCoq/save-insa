#include <stdio.h>

int main(int argc, char ** argv, char ** env)
{

	int i;
	for( i = 0; i < argc; i++)
	{
		printf("L'argument %d est %s\n", i, argv[i]);
	}
	i = 0;
	while ( env[i] != NULL )
	{
		printf("La variable d'environnement %d est %s\n", i, env[i]);
		i++;
	}

	return 0;

}
