
#include <stdio.h>
#include <math.h>

int chaine_longueur_rec(char *s)
{
    if ( *s == 0 )
    {
        return 0;
    }
    return (1 + chaine_longueur_rec( s+1));
}

int chaine_debute_par( char *s1, char *s2)
{
    if ( *s2 == 0 )
    {
       return 1;
    }
    else 
    {
        if ( *s1 != *s2 )
        {
            return 0;
        }
        else 
        {
            return chaine_debute_par(s1 + 1, s2 + 1);
        }
    }
}



int main(void)
{
    char c1[20];
    char c2[20];
    char c3[20];
    printf("Entrez une chaine de caractere pour connaitre sa longueur : ");
    scanf("%s", &c1);
    printf("la longuer de la chaine est : %d\n",chaine_longueur_rec(c1));
    
    printf("Saisissez une premiere chaine : ");
    scanf("%s", &c2);
    printf("Saisissez une seconde chaine pour voir si la précédente commence par celle ci : ");
    scanf("%s", &c3);
    printf("Résulat : %d\n", chaine_debute_par(c2,c3));

    return 0;    
}
