#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int new_ls(const char *ref){
	struct stat info;
	if(lstat(ref, &info) != -1)
	{
        	char type;
		#define LTEMPS 32
		char pws[9], grs[9], temps[LTEMPS], curfile[1024];
		struct passwd * pw = getpwuid(info.st_uid);
        	if ( pw != NULL ) strcpy(pws, pw->pw_name);
        	else printf("%8li\n", info.st_uid);

	        struct group * gr = getgrgid(info.st_gid);
	        if ( gr != NULL ) strcpy(grs, gr->gr_name);
	        else printf("%8li\n", info.st_gid);
        
		strcpy(curfile, ref);

		type = '?';
	        if ( S_ISREG(info.st_mode)) { type = '-'; }
	        else if ( S_ISDIR(info.st_mode) ) { type = 'd'; }
	        else if ( S_ISCHR(info.st_mode) ) { type = 'c'; }
	        else if ( S_ISBLK(info.st_mode) ) { type = 'b'; }
	        else if ( S_ISFIFO(info.st_mode) ) { type = 'f'; }
	        else if ( S_ISLNK(info.st_mode) ) { 
			type = 'l'; 
			char buf[1024];
			char *res;
		// Possibilité d'utiliser readlink pour seulement avoir le nom du fichier pointer par le lien
			if ( (readlink(ref, buf, 1024)))
			{
				strcat(curfile, " -> ");
				strcat(curfile, buf);
			}
		}
	        else if ( S_ISSOCK(info.st_mode) ) { type = 's'; }
	
		strftime(temps, LTEMPS, "%e %h %Y %H:%M", localtime(&info.st_mtime));

		printf("%c%c%c%c%c%c%c%c%c%c %8s %8s %li %s %s\n",
			type,
			info.st_mode&S_IRUSR?'r':'-',
			info.st_mode&S_IWUSR?'w':'-',
			info.st_mode&S_IXUSR?'x':'-',
			info.st_mode&S_IRGRP?'r':'-',
              		info.st_mode&S_IWGRP?'w':'-',
                	info.st_mode&S_IXGRP?'x':'-',
			info.st_mode&S_IROTH?'r':'-',
                	info.st_mode&S_IWOTH?'w':'-',
                	info.st_mode&S_IXOTH?'x':'-',
			pws,
			grs,
			info.st_size,
			temps,
			curfile
			);
		return 0;
	}
	else
	{
		perror("no such path");
		return 0;
	}
}

int listRep(char * rep)
{
	DIR *dirp;
	struct dirent *dp;
	struct stat info;
	char BUFFER[256];
	if ((dirp = opendir(rep)) == NULL)
	{
		new_ls(rep);	
		return 0;
	}
	else
	{
		while((dp = readdir(dirp)))
		{

			snprintf(BUFFER, 256, "%s/%s", rep, dp->d_name);
			
			if (dp->d_type==DT_DIR && dp->d_type!=DT_LNK)
			{
				if(lstat(BUFFER, &info) != -1) new_ls(BUFFER);	
				printf("\n %s : \n", BUFFER);
				listRep(BUFFER);
			}
			else
			{
				if(lstat(BUFFER, &info) != -1)
				{
					new_ls(BUFFER);
				}
			}
			
		}
		
	}
	closedir(dirp);
	return 0;
}

int main(int argc, char ** argv)
{
	if ( argc < 2 )
	{
		printf("Wrong usage of cmd. Usage ./ls <files>");
		exit(EXIT_FAILURE);
	}
	else
	{
		int i;
		for ( i=1; i<argc; i++)
		{
			listRep(argv[i]);
		}
		exit(EXIT_SUCCESS);
	}
}


