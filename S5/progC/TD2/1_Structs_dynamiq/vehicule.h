#ifndef __VEHICULE_H__
#define __VEHICULE_H_

typedef struct vehicule {
	char nom_modele[20];
	int puissance;
	float vitesse_max;
} vehicule;

void init_vehicule(vehicule *);

#endif
