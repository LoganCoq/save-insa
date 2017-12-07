#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void ls_lh(const char *ref, struct stat *status)
{
	struct passwd *psw;
	struct group *grp;
	char type;
	#define LTEMPS 32
	char psws[9], grps[9], temps[LTEMPS];
	
	type = '?';
	if (S_ISREG(status->st_mode)) type = '-';
	else if (S_ISDIR(status->st_mode)) type = 'd';
	else if (S_ISCHR(status->st_mode)) type = 'c';
	else if (S_ISBLK(status->st_mode)) type = 'b';
	else if (S_ISFIFO(status->st_mode)) type = 'p';
	else if (S_ISLNK(status->st_mode)) type = 'l';

	strftime(temps, LTEMPS, "%e %h %Y %H:%M", localtime(&status->st_mtime));
	psw = getpwuid(status->st_uid);
	if (psw != NULL) strcpy(psws, psw->pw_name);
	else sprintf(psws, "%8d", (int)status->st_uid);

	grp = getgrgid(status->st_gid);
	if (grp != NULL) strcpy(grps, grp->gr_name);
	else sprintf(grps, "%8d", (int)status->st_gid);

	printf("%c%c%c%c%c%c%c%c%c%c %8s %8s %9d %s %s\n",
		type,
		status->st_mode&S_IRUSR?'r':'-',
		status->st_mode&S_IWUSR?'w':'-',
		status->st_mode&S_IXUSR?'x':'-',
		status->st_mode&S_IRGRP?'r':'-',
		status->st_mode&S_IWGRP?'w':'-',
		status->st_mode&S_IXGRP?'x':'-',
		status->st_mode&S_IROTH?'r':'-',
		status->st_mode&S_IWOTH?'w':'-',
		status->st_mode&S_IXOTH?'x':'-',
		psws,
		grps,
		(int)status->st_size,
		temps,
		ref);
}

int main(int argc, char * argv[])
{
	struct stat status;
	int i;
	if (argc == 2)
	{
		if ( fstat(STDIN_FILENO, &status) == -1)
		{
			fprintf(stderr, "%s: impossible d'obtenir le status de %s\n", argv[0], "<STDIN>");
			exit(EXIT_FAILURE);
		}
		ls_lh("<STDIN>", &status);;
	}
	else 
	{
		for ( i=1; i<argc; i++)
		{
			if (fstat(*argv[i],&status) == -1)
			{
				fprintf(stderr, "%s: impossible d'obtenir le status de %s\n", argv[0], argv[i]);
				continue;
			}
			ls_lh(argv[i], &status);
		}
	}
	exit(EXIT_SUCCESS);
}

