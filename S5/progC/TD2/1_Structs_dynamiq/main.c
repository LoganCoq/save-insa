#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "vehicule.h"


int main()
{
	vehicule * v1;
	v1 = NULL;
	v1 = malloc(sizeof(vehicule));
	init_vehicule(v1);

	printf("%d , %f\n", v1->puissance, v1->vitesse_max);

	return 0;
}
