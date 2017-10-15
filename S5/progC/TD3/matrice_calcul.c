#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "alloc.h"
#include "matrice_calcul.h"
#include "matrice_io.h"

matrice add_matrice(matrice m1, matrice m2)
{
    if(m1.nb_lignes != m2.nb_lignes || m1.nb_colonnes != m2.nb_colonnes)
    {
        perror("addition");
    }
    matrice newM;
    newM = allouer_matrice(m1.nb_lignes, m1.nb_colonnes);

    int i, j;
    for( i = 0; i < m1.nb_lignes; i++)
    {
        for ( j = 0; j < m1.nb_colonnes; j++)
        {
            newM.m[i][j] = m1.m[i][j] + m2.m[i][j];
        }
    }
    return newM;
}

matrice multiply_matrice(matrice m1, matrice m2)
{
    if(m1.nb_lignes != m2.nb_colonnes || m1.nb_colonnes != m2.nb_lignes)
    {
        perror("multiplication");
    }
    matrice newM;
    newM = allouer_matrice(m1.nb_lignes, m2.nb_colonnes);
    affiche_matrice(newM);
    int i, j, k;
    for ( i = 0; i < m1.nb_lignes; i++)
    {
        for ( j = 0; j < m2.nb_colonnes; j++)
        {
            for ( k = 0; k < m1.nb_colonnes; k++)
            {
                newM.m[i][j] += m1.m[i][k] * m2.m[k][j];
            }
        }
    }
    return newM;
}
