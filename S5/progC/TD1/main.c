

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "produit.h"

int main(void)
{
    int a, b, c;
    float d;	
    scanf("%d", &a);
    scanf("%d", &b);
    c = produit(a, b);
    printf("\nle produit vaut %d\n", c);
    d = moy_geo(a, b);
    printf("\nla moyenne geometrique vaut %f\n", d);
    return EXIT_SUCCESS;
}
