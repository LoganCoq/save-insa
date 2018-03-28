/**
 * \file gcd.c
 * \brief Gcd algorithm library
 * \author Rosetta code project
 * \version 1.0
 * \date 2018, March, 1rst
 *
 * Library containing different gcd algorithm implementation, coming from Rosetta project 
 * http://www.rosettacode.org/
 */

/**
 * \fn int gcd_iter(int u, int v)
 * \brief Iterative gcd algorithm
 *
 * \param u one number 
 * \param v another number 
 * \return gcd
 */

int gcd_iter(int u, int v) {
  if (u < 0) u = -u;
  if (v < 0) v = -v;
  if (v) while ((u %= v) && (v %= u));
  return (u + v);
}

/**
 * \fn int gcd(int u, int v)
 * \brief Euclide gcd algorithm
 *
 * \param u one number 
 * \param v another number 
 * \return gcd
 */

int gcd(int u, int v) {
return (v != 0)?gcd(v, u%v):u;
}

/**
 * \fn int gcd_bin(int u, int v)
 * \brief Binary gcd algorithm
 *
 * \param u one number 
 * \param v another number 
 * \return gcd
 */

int gcd_bin(int u, int v) {
  int t, k;
 
  u = u < 0 ? -u : u; /* abs(u) */
  v = v < 0 ? -v : v; 
  if (u < v) {
    t = u;
    u = v;
    v = t;
  }
  if (v == 0)
    return u;
 
  k = 1;
  while (u & 1 == 0 && v & 1 == 0) { /* u, v - even */
    u >>= 1; v >>= 1;
    k <<= 1;
  }
 
  t = (u & 1) ? -v : u;
  while (t) {
    while (t & 1 == 0) 
      t >>= 1;
 
    if (t > 0)
      u = t;
    else
      v = -t;
 
    t = u - v;
  }
  return u * k;        
}
