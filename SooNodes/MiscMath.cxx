// (c) Dominique Attali 2003 (LIS)

#include <stdio.h>
#include <math.h>
#include "MiscMath.h"

bool COMPARISON_INT_WEIGHTED(INT_WEIGHTED i, INT_WEIGHTED j) { return (i.second<j.second); }


// Affiche l'entier n en base 2
// en supposant que les entiers se codent sur
// 32 bits.
void
PrintBinary(int n)
{
  int b;
  printf("%d :                                 ", n); fflush(stdout);
  for (int i=0;i<32;i++)
    {
      b = n&1;
      printf("%1d\010\010",b);fflush(stdout);
      n=n>>1;
    }
  printf("\n");
}

void vectoriel(double * u, double * v, double * w)
{
  w[0] = u[1]*v[2]-u[2]*v[1];
  w[1] = u[2]*v[0]-u[0]*v[2];
  w[2] = u[0]*v[1]-u[1]*v[0];
}

// Normalise le vecteur v!=0
int normalize(double * v)
{
  double l = v[0]*v[0]+v[1]*v[1]+v[2]*v[2];
  if (l==0.0) return 0;
  if( l!=1.0 && l!=0.0 )
    {
      l = sqrt(l);
      v[0]/=l;
      v[1]/=l;
      v[2]/=l;
    }
  return 1;
}

int normal(double * a, double * b, double * c, double * n)
{
  double u[3] = { b[0]-a[0], b[1]-a[1], b[2]-a[2] };
  double v[3] = { c[0]-a[0], c[1]-a[1], c[2]-a[2] };
  vectoriel(u,v,n);
  return normalize(n);
}

double scalaire(double * u, double * v)
{
  return u[0]*v[0]+u[1]*v[1]+u[2]*v[2];
}

void middle(double * a, double * b, double * m)
{
  m[0] = (a[0] + b[0]) / 2.0;
  m[1] = (a[1] + b[1]) / 2.0;
  m[2] = (a[2] + b[2]) / 2.0;
}

// Le point m interpole lineairement les points a et b
void
linear_interpolation(double * a, double * b, double * m, double ha, double hb, double hm)
{
  double lambda = (hm-ha) / (hb-ha);
  for (int i=0;i<3;i++)
    m[i] = lambda * (b[i]-a[i]) + a[i];
}

// Le point m interpole lineairement les points a et b
void
secure_linear_interpolation(double * a, double * b, double * m, double ha, double hb, double hm, double coef)
{
  double lambda = (hm-ha) / (hb-ha);
  if (lambda > 1.0-coef) lambda = 1.0 - coef;
  if (lambda < coef) lambda = coef;
  for (int i=0;i<3;i++)
    m[i] = lambda * (b[i]-a[i]) + a[i];  
}

double distance(double * a, double * b)
{
  return sqrt((a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1])+(a[2]-b[2])*(a[2]-b[2]));
}
