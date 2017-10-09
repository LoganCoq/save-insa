#include <stdlic.h>
#include <stdio.h>
#include "matrice.h"
#include "alloc.h"

int main(void)
{
	struct matrice m1;
	m1 = allouer_matrice(5,5);
	
	return 0;

}
