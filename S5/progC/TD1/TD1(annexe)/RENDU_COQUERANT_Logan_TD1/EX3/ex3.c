
#include <stdio.h>
#include <math.h>

#define ZERO 1e-100
#define EPSILON 1e-10

int proche(double a, double b)
{
    return fabs(a) < ZERO ? fabs(b) < ZERO : fabs(a-b) < EPSILON * fabs(a);
}

double moyenne(double t[], int n)
{
    int i;
    double res = 0.0;
    for (i = 0; i < n; ++i)
    {
        res += t[i];
    }
    return res / n;
}

double moyenne_positifs(double t[]) 
{
    int i;
    double res = 0.0;
    for ( i = 0; t[i] > 0; ++i)
    {
        res += t[i];  
    }
    if ( i == 0 && t[i] < 0 ){
        return -1.0;
    }
    return res / i;
}

double test_moyenne()
{
    double v[]= {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, -1.0};
    double d, attendu;
    attendu = 1;
    if (! proche ((d = moyenne (v, 1)), attendu )) 
    {
        printf (" Pb moyenne . Attendu : %f Obtenu :%f\n",attendu,d);
    }
    attendu = 2.0;
    if (! proche ((d = moyenne (v, 3)), attendu )) 
    {
        printf (" Pb moyenne . Attendu : %f Obtenu :%f\n",attendu,d);
    }
    attendu = 3.5;
    if (! proche ((d = moyenne (v, 6)), attendu )) 
    {
        printf (" Pb moyenne . Attendu : %f Obtenu :%f\n",attendu,d);
    }
    attendu = 3.5;
    if(! proche ((d = moyenne_positifs (v)), attendu )) 
    {
        printf (" Pb moyenne_positifs . Attendu : %f Obtenu :%f\n", attendu , d);
    }
    attendu = 5.0;
    if(! proche ((d = moyenne_positifs (v+3)), attendu )) 
    {
        printf (" Pb moyenne_positifs . Attendu : %f Obtenu :%f\n", attendu , d);
    }
    attendu = -1.0;
    if(! proche ((d = moyenne_positifs (v+6)), attendu )) 
    {
        printf (" Pb moyenne_positifs . Attendu : %f Obtenu :%f\n", attendu , d);
    }
}



int main() 
{
    test_moyenne();
    return 0;
}
