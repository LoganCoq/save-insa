#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "vehicule.h"

void init_vehicule(vehicule * v)
{
	srand(time(NULL));
	v->puissance = rand();
	v->vitesse_max = rand();
}
