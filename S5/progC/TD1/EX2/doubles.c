
#include <math.h>
#include "doubles.h"

int proche(double a, double b)
{
    double delta;
    delta = fabs(a - b);
    
    if ( delta < ZERO || delta <= EPSILON )
    {
        return 1;
    } else {
        return 0;
    }
    

}
