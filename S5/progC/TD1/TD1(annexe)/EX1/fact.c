
#include "fact.h"
#include <limits.h>

int factor(int n)
{
    int i = 1;
    int f = 1;
    for (i = 1; i <= n; ++i)
    {
        if (INT_MAX/n > f)
        {
            f *= i;
        }
        else 
        {
            return -1;
        }
    }
    return(f);
}

int factor_recurs(int n)
{
    if (n <= 0)
    {
        return 1;
    }
    else 
    {
        if ( INT_MAX/n > factor_recurs(n-1))
        {
            return n*factor_recurs(n-1);
        }
        else 
        {
            return -1;
        }
    }
}
