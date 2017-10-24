#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>

void get_user_content(char * name);

int main(int argc, char ** argv)
{
	get_user_content(argv[1]);	
	return EXIT_SUCCESS;
}

void get_user_content(char * name)
{
	struct passwd *user;
	user = getpwnam(name);
	if (user != NULL)
	{
		printf("Nom : %s\n", user->pw_name);
		printf("Passwd : %s\n", user->pw_passwd);
		printf("UID : %i\n", user->pw_uid);
		printf("GID : %i\n", user->pw_gid);
		printf("Nom du groupe %s\n", user->pw_gecos);
		printf("Directory %s\n", user->pw_dir);
		printf("Shell %s\n", user->pw_shell);
	}
	else {
		printf("Utilisateru incunnu\n");
	}
}

// for i in `ldapsearch -x | grep "^uid:" | cut -d" " -f2`;do ./exo5 $i;done

