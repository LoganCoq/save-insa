/* file name  : liste.c
 * authors    : Simon MORIN / JF Lalande
 * created    : dim 08 jan 2006 16:36:13 CET
 * copyright  : ENSIB
 *
 * modifications:
 * - Le premier élément est désormais un élément "de gestion". Il ne contient
 *   pas de vehicule. Lorsque la liste est vide, le premier element contient:
 *   l->v = NULL;
 *   l->next = NULL;
 * - Par consequent, le "vrai" premier element est juste apres.
 * - Quelques fonctions ont ete renommees.
 *
 */
#include <stdlib.h>
#include <string.h>
#include "liste.h"

// Initialise une liste vide
liste_vehicule * init_liste()
{
	liste_vehicule *temp = (liste_vehicule *) malloc(sizeof(liste_vehicule));
	temp->v = NULL;
	temp->next = NULL;
  temp->size = 0;
	return temp;
}

// Ajoute un vehicule en queue
void add_vehicule(vehicule *v,liste_vehicule * l)
{

  // On augmente la taille
  l->size++;

  // Puis on ajoute
	if (l->next != NULL)
  {
		add_vehicule(v,l->next);
	}
	else
  {
		l->next = (liste_vehicule *) malloc(sizeof(liste_vehicule));
		l->next->v = v;
		l->next->next = NULL;
	}
}

// Ajoute un vehicule en tete
void add_vehicule_head(vehicule *v, liste_vehicule *l) {
  liste_vehicule *nouv = (liste_vehicule *) malloc(sizeof(liste_vehicule));
  nouv->v = v;
  nouv->next = l->next;
  l->next = nouv;
  l->size++;
}

// Enleve le premier vehicule et le retourne
vehicule * remove_first_vehicule(liste_vehicule * l)
{
	vehicule *v;
  v = l->next->v;
	l->next = l->next->next;
  l->size--;
	return v;
}

// Retourne la tete de la liste
vehicule * get_first_vehicule(liste_vehicule * l)
{
  if (l->next != NULL)
  {
    return l->next->v;
  }
  else
  {
    return NULL;
  }
}

// Retourne le dernier element de la liste
vehicule *get_last_vehicule(liste_vehicule * l)
{
  if (l->next != NULL)
  {
    return get_last_vehicule(l->next);
  }
  else
  {
    return l->v;
  }
}

// Detruit la liste des vehicules et les vehicules
void destroy_list_and_vehicules(liste_vehicule * l)
{
	if(l->next != NULL){
		destroy_list_and_vehicules(l->next);
	}

	if(l->v != NULL) {
           destroy_vehicule(l->v);
        }
        else {
           l->size = 0;
        }
	free(l);

}

// Taille de la liste
int size(liste_vehicule * l)
{
  return l->size;
}

// Retourne un pointeur sur vÃ©hicule grÃ¢ce Ã  son nom dans une liste
vehicule* cherche_vehicule(char nom[20], liste_vehicule * L)
{
	if ( L->size == 0 && L->v == NULL) 
	{
		return NULL;
	}
	else if ( L->v == NULL )
	{
		return cherche_vehicule(nom, L->next);
	}
	else if ( strcmp(L->v->nom_modele, nom) == 0 )
	{
		return L->v;
	}
	else 
	{
		return cherche_vehicule(nom, L->next);
	}
}

// Enleve un vehicule d'une liste grÃ¢ce Ã  son nom_modele
vehicule* enlever_vehicule(char nom[20], liste_vehicule * L)
{
	if ( L->size == 0 && L->v == NULL) 
        {
                return NULL;
        }
        else if ( strcmp(L->next->v->nom_modele, nom) == 0 )
        {
		vehicule *v;
		v = L->next->v;
		liste_vehicule *lvTmp = L->next;
		L->next = L->next->next;
		free(lvTmp);

		L->size--;
                return v;
        }
        else 
        {
		vehicule *v = enlever_vehicule(nom, L->next);
		if (v != NULL) L->size--;
                return v;
        }
}

//Renverse la liste
liste_vehicule* renverser_liste(liste_vehicule *L)
{
	int i;
	liste_vehicule *nlv;
	nlv = init_liste();
	for ( i = 0; i < L->size; i++ )
	{
		
		add_vehicule_head(get_last_vehicule(L),nlv);
		enlever_vehicule(get_last_vehicule(L));
	}
	return nlv;
}
