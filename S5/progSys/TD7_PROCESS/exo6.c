#include <unistd.h>
#include <stdlib.h>



int main(int argc, char ** argv, char ** envp)
{
	int pid = fork();
	char * args[3];
	args[0] = "/bin/ls";
	args[1] = "-l";
	args[2] = NULL;
	execve("/bin/ls", args, envp);
	exit(EXIT_SUCCESS);
}
