#ifndef COMMUN_H
#define COMMUN_H

#define NOM "commun.h"
#define PROJ_FTOK_SEM 'a'
#define PROJ_FTOK_MEM '0'

#define TAILLE 20
#define N 5

ushort init_sem[]={1,N};
 struct sembuf demande_ecriture[]={{0,-1,SEM_UNDO},{1,-N,SEM_UNDO}};  /* {ecrivain :{cmpt, cmpt-1, undo},lecteur : {cmpt, cmpt-5}*/
/* sembuf -> operation à effectuer sur une semaphore */
struct sembuf stoppe_ecriture[]={{0,+1,SEM_UNDO},{1,N,SEM_UNDO}};

struct sembuf demande_lecture={1,-1,SEM_UNDO}; /*n'influt pas sur les ecrivains*/
struct sembuf stoppe_lecture={1,+1,SEM_UNDO};
#endif


