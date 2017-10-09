#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "fact.h"


int main(void)
{
    int n;
    printf("%d", INT_MAX);
    do 
    {
        printf("Entrez un nombre entier (0 pour terminer): ");
        scanf("%d", &n);
        printf(" factorielle_iterative (%2d) = %15d\n", n, factor(n));
        printf(" factorielle_recursice (%2d) = %15d\n", n, factor_recurs(n));
    } while ( n!= 0);
    return 0;

}
