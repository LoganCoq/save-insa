#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

/*
int main(void)
{
	//creation de la pile
	struct pile *p1 = cree_pile();
	printf("%p\n", p1);
	//liberation de la memoire occupée par la pile
	libere_pile(p1);
	//printf("%p\n", p1);

	struct pile *p2 = cree_pile();
	printf("%p\n", p2);
	ajoute_pile(p2, 5);
	printf("ajoute_pile 5 : %p , %d \n",p2->tab, p2->curseur);

        ajoute_pile(p2, 2);
        printf("ajoute_pile 2 : %p , %d \n",p2->tab, p2->curseur);

	printf("retire_pile : %d, %d\n", retire_pile(p2), p2->curseur);
	libere_pile(p2);


	return 0;
}
*/

int main() {
  /*
  Notez qu’il n’ya pas besoin de connaitre la structure interne de la pile.
  Le même programme pourra être utilise avec une autre implémentation.
  */
  int c, n;
  pile * p = cree_pile();
  if (p == NULL) {
    /*
    on ne devrait pas passer par la, mais bonne habitude
    */
    fprintf(stderr, "Création de pile impossible. Contacter l’administrateur\n");
    getchar();
    return 1;
  }
  do {
    /*exemple de menu
     */
    printf("\n");
    printf("1. Empiler \n");
    printf("2. Depiler \n");
    printf("3. Sommet \n");
    printf("4. Affichage \n");
    printf("\n");
    printf("0. Quitter \n");
    printf("Votre choix : ");
    scanf("%d", & c);
    switch (c) {
    case 1:
      if (pile_pleine(p)) {
        printf("Pile pleine. Empilement impossible");
        break;
      }
      printf("Empilement. Entrez le nombre a empiler : ");
      scanf("%d", & n);
      ajoute_pile(p, n);
      break;
    case 2:
      if (pile_vide(p)) {
        printf("Pile vide. Dépilement impossible");
        break;
      }
      printf("Dépilement de %d\n", retire_pile(p));
      break;
    case 3:
      if (pile_vide(p)) {
        printf("Pile vide. Pas de sommet ");
        break;
      }
      printf("Sommet : %d\n", sommet_pile(p));
      break;
    case 4:
      printf("Affichage :");
      affiche_pile(p);
      printf("\n");
      break;
    }
  } while (c != 0);
  /*
  bonne habitude de toujours libérer ce que l’on a alloue
  */
  libere_pile(p);
  getchar();
  return 0;
}
