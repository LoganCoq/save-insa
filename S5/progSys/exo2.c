#include <stdio.h>
#include <stdlib.h>

extern char ** environ;

void getValEnv( const char *var );
void putKeyVal(const char *key, const char *val);

int main(int argc, char ** argv)
{
	char **ptr = environ;
	while (*ptr!=NULL)
	{
		printf("%s\n", *ptr);
		ptr++;
	}
	
	printf("%s\n",getenv("LANG"));
	getValEnv("LANG");

	return 0;	
}

void getValEnv( const char *var)
{
	printf("%s\n", getenv(var));
}

