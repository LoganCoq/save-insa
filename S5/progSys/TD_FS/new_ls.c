#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int new_ls(struct stat info){
        char type;
	char pws[9], grs[9];
	struct passwd * pw = getpwuid(info.st_uid);
        if ( pw != NULL )
        {
		strcpy(pws, pw->pw_name);
        } else
        {
        	printf("%li\n", info.st_uid);
        }
        struct group * gr = getgrgid(info.st_gid);
        if ( gr != NULL )
        {
        	strcpy(grs, gr->gr_name);
        } else {
        	printf("%s\n", info.st_gid);
        }        
        if ( S_ISREG(info.st_mode)) { type = '-'; }
        else if ( S_ISDIR(info.st_mode) ) { type = 'd'; }
        else if ( S_ISCHR(info.st_mode) ) { type = 'c'; }
        else if ( S_ISBLK(info.st_mode) ) { type = 'b'; }
        else if ( S_ISFIFO(info.st_mode) ) { type = 'f'; }
        else if ( S_ISLNK(info.st_mode) ) { type = 'l'; }
        else if ( S_ISSOCK(info.st_mode) ) { type = 's'; }

	printf("%c%c%c%c%c%c%c%c%c%c %s %s %li\n",
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
		info.st_size
		
		);
	exit(EXIT_SUCCESS);
}

int main(int argc, char ** argv)
{
	struct stat info;
	char type;
	if ( stat(argv[1], &info) != -1 )
	{
		new_ls(info);
		exit(EXIT_SUCCESS);		
	}
	else
	{
		perror("no such path"); 
		exit(EXIT_FAILURE);
	}
}


