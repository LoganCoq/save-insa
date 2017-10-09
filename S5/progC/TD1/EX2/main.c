#include <stdlib.h>
#include <stdio.h>
#include "doubles.h"


int main(void)
{
    double a, b;
    
    do 
    {
        printf("Entrez un double a : ");
        scanf("%lf", &a);
        printf("Entrez un double b : ");
        scanf("%lf", &b);

        printf("proches : %d\n", proche(a,b));
    } while ( a > 0 && b > 0);
    return 0;

}
