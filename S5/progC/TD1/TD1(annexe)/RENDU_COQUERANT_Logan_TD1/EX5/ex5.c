#include <stdio.h>
#include "ex5.h"

int chaine_indice(char s1[], char s2[])
{
    int i;
    for ( i = 0; i < 20 ; ++i)
    {
        if ( s1[i] == s2[0] )
        {
            return i;
        }
    }
    return -1;
}
