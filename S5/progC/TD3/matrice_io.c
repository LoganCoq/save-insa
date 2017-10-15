#include <stdio.h>
#include <stdlib.h>
#include "matrice_io.h"
#include "alloc.h"

matrice read_matrice(FILE * p)
{
	matrice m;
	int nbLignes = 0;
	int nbColonnes = 0;
	int curRow = 0;
	int val;
	int pos = 0;
	int step = 0;
	if ( p )
	{
		while(fscanf(p, "%d", &val)!=EOF)
		{
			if(step == 0) {
				nbLignes = val;
				step++;
			}
			else if(step == 1){
				nbColonnes = val;
				m=allouer_matrice(nbLignes, nbColonnes);
				step++;
			}
			else {
				if ( pos%nbColonnes == 0 && pos != 0)
				{
					curRow++;
				}
				m.m[curRow][pos%nbColonnes] = val;
				pos++;
			}
		}
	}
	return m;
}

void write_matrice(FILE * p, matrice m)
{
	int i, j;
	if(p)
	{
		fprintf(p, "%d %d\n", m.nb_lignes, m.nb_colonnes);
		for( i = 0; i<m.nb_lignes; i++)
		{
			for ( j = 0; j < m.nb_colonnes; j++)
			{
				fprintf(p, "%d ", m.m[i][j]);
			}
			fprintf(p, "\n");
		}
	}
}

void affiche_matrice(matrice m)
{
	int i, j;
	printf("%d %d\n", m.nb_lignes, m.nb_colonnes);
	for ( i = 0; i < m.nb_lignes; i++)
	{
		for( j = 0; j < m.nb_colonnes; j++)
		{
			printf("%d ", m.m[i][j]);
		}
		printf("\n");
	}
}
