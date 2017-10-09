#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

pile * cree_pile()
{
	pile * newPile;
	newPile = NULL;
	newPile = malloc(sizeof(pile));
	if (!newPile)
	{
		printf("memoire vide \n");
		exit(EXIT_FAILURE);
	}
	newPile->curseur = 0;
	return newPile;
}


void libere_pile(pile *p)
{
	free(p);
	p = NULL;
}

void ajoute_pile(pile *p, int n)
{
	p->tab[p->curseur] = n;
	p->curseur++;
}

int retire_pile(pile *p)
{
	p->curseur--;
	return p->tab[p->curseur];
}

int sommet_pile(pile *p)
{
	return p->tab[p->curseur - 1]; 
}

int pile_vide(pile *p)
{
	return p->curseur == 0;
}

int pile_pleine(pile *p)
{
	return p->curseur == TMAX;
}

void affiche_pile(pile *p)
{
	printf("(");
	int i;
	if ( !pile_vide(p) )
	{
		printf("%d",p->tab[0]);
		for ( i = 1; i < p->curseur; i++)
		{
			printf(", %d", p->tab[i]);
		}
	}
	printf(")\n");
}
