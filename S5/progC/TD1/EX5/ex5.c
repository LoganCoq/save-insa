#include <stdio.h>

int chaine_indice(char * s1, char *s2)
{
    int i;
    for ( i = 0; i < sizeof(s1); ++i)
    {
        if ( s1[i] == s2[0] )
        {
            return i;
        }
    }
    return -1;
}


int main(void)
{
    char c1[20];
    char c2[1];

    printf("Veuillez saisir une chaine de caractères : ");
    scanf("%s", &c1);
    printf("Veuillez saisir un caractère pour trouver sa position dans la chaine : ");
    scanf("%s", &c2);
    

    int res = chaine_indice(c1, c2);
    if ( res == -1 )
    {
        printf("Ce caractères n'est pas présent dans la chaine %s\n", c1);
    }
    else {
        printf("Ce caractères est présent à l'indice : %d\n", res);
    }

    return 0;
}
