/**
 * \file lcm.c
 * \brief lcm library
 * \author Rosetta code project
 * \version 1.0
 * \date 2018, March, 1rst
 *
 * Library containing an lcm algorithm coming from Rosetta project 
 * http://www.rosettacode.org/
 */

#include <stdio.h>
#include "gcd.h"

/**
 * \fn int lcm(int u, int v)
 * \brief lcm algorithm
 *
 * \param u one number 
 * \param v another number 
 * \return lcm
 */

 
int lcm(int m, int n)
{
        return m / gcd(m, n) * n;
}
