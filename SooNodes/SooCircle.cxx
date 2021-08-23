// (c) Dominique Attali 2003 (LIS)

#include <stdio.h>
#include <math.h>
#include "SooCircle.h"
#include "MiscMath.h"

void
SooCircle::by_default()
{
  setCenter(0.0, 0.0, 0.0);
  setRadius(1.0);
  setAxe(0.0,0.0,1.0);
}

SooCircle::SooCircle() : SooDrawable("Circle")
{
  by_default();
}

SooCircle::SooCircle(double * c, double r, double * a) : SooDrawable("Circle")
{
  setCenter(c[0],c[1],c[2]);
  setRadius(r);
  setAxe(a[0],a[1],a[2]);
}

void
SooCircle::draw()
{
  int k, n=60;
  double alpha;			// Angle courant
  double x , y;			// Point courant en coordonnees locales dans le plan (u,v)
  double u[3], v[3];		// Repere construit a partir de l'axe
  double m[3];			// Point courant du cercle dans l'espace R3
  double i[3] = {1.0, 0.0, 0.0};
  double j[3] = {0.0, 1.0, 0.0};

  vectoriel(axe,i,u);
  if ((u[0]==0.0)&&(u[1]==0.0)&&(u[2]==0.0))
    vectoriel(axe,j,u);
  vectoriel(axe,u,v);
  normalize(u);
  normalize(v);
    
  glBegin( GL_LINE_LOOP );
  for (k=0;k<n;k++)
    {
      alpha = (double)k/(double)n*2.0*M_PI;
      x = radius * cos(alpha);
      y = radius * sin(alpha);
      m[0] = center[0] + x*u[0] + y*v[0];
      m[1] = center[1] + x*u[1] + y*v[1];
      m[2] = center[2] + x*u[2] + y*v[2];
      glVertex3dv(m);
    }
  glEnd();
}

void
SooCircle::setCenter(double x, double y, double z)
{
  center[0] = x;
  center[1] = y;
  center[2] = z;
  touch();
}

void
SooCircle::getCenter(double &x, double &y, double &z)
{
  x = center[0];
  y = center[1];
  z = center[2];  
}

void
SooCircle::setRadius(double r)
{
  radius = r;
  touch();
}

double
SooCircle::getRadius()
{
  return radius;
}

void
SooCircle::setAxe(double x, double y, double z)
{
  axe[0] = x;
  axe[1] = y;
  axe[2] = z;
  touch();
}

void
SooCircle::getAxe(double &x, double &y, double &z)
{
  x = axe[0];
  y = axe[1];
  z = axe[2];  
}
