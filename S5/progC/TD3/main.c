#include <stdlib.h>
#include <stdio.h>
#include "matrice.h"
#include "alloc.h"
#include "matrice_io.h"
#include "matrice_calcul.h"


int main (void)
{
	matrice m1,m2,m;
	FILE* matrice;

//---lecture des matrice pour l'addition-----
	matrice=fopen("add_m1.txt","r");
	m1=read_matrice(matrice);
	printf("\n");
	printf("Affichage d'une matrice m1 pour l'addition:\n");
	affiche_matrice(m1);
	fclose(matrice);
	printf("\n");

	matrice=fopen("add_m2.txt","r");
	m2=read_matrice(matrice);
	printf("Affichage d'une matrice m2 pour l'addition:\n");
	affiche_matrice(m2);
	fclose(matrice);
	printf("\n");
//-------------------------------------------


//----addition+affichage+sauvegarde----------
	m=add_matrice(m1,m2);//addition et sauvegarde
	printf("Resultat de l'ADDITION de la matrice m1 et m2:\n");
	affiche_matrice(m);//affichage
	matrice=fopen("add.txt","w");
	write_matrice(matrice, m1);
	fclose(matrice);
	printf("\n");
//-------------------------------------------


//---lecture des matrices pour la multiplication-----
	matrice=fopen("mult_m1.txt","r");
	m1=read_matrice(matrice);
	printf("Affichage d'une autre matrice m1 pour la multiplication:\n");
	affiche_matrice(m1);
	fclose(matrice);
	printf("\n");

	matrice=fopen("mult_m2.txt","r");
	m2=read_matrice(matrice);
	printf("Affichage d'une autre matrice m2 pour la multiplication:\n");
	affiche_matrice(m2);
	fclose(matrice);
	printf("\n");
//--------------------------------------------------


//----addition+affichage+sauvegarde----------
	m=multiply_matrice(m1,m2);//multiplication et sauvegarde
	printf("Resultat de la MULTIPLICATION de m1 et m2:\n");
	affiche_matrice(m);//affichage

	matrice=fopen("mult.txt","w");
	write_matrice(matrice, m);
	fclose(matrice);
	printf("\n");
//-------------------------------------------


	detruire_matrice(&m);
	detruire_matrice(&m1);
	detruire_matrice(&m2);
	return 0;
}
