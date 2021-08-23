// (c) Dominique Attali 2003 (LIS)

#include <iostream>
#include "SooSphere.h"

using std::cout;


void
SooSphere::by_default(float x, float y, float z, float r)
{
  setCenter(x,y,z);
  setRadius(r);
  slices = 16;
  stacks = 16;
}

void
SooSphere::by_default()
{
  by_default(0.0, 0.0, 0.0, 1.0);
}

SooSphere::SooSphere() : SooDrawable("Sphere")
{
  by_default();
}

SooSphere::SooSphere(float x, float y, float z, float r) : SooDrawable("Sphere")
{
  by_default(x,y,z,r);
}

SooSphere::SooSphere(float * c, float r) : SooDrawable("Sphere")
{
  by_default(c[0],c[1],c[2],r);
}

// borrowed from aux and GLUT
// choices: GLU_FILL,GLU_LINE,GLU_SILHOUETTE,GLU_POINT
void
SooSphere::draw()
{
  glPushMatrix();
  glTranslatef(center[0], center[1], center[2]);
  glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
  glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
  GLUquadricObj *quadObj = gluNewQuadric ();
  gluQuadricDrawStyle (quadObj, (GLenum)GLU_FILL);
  gluQuadricNormals (quadObj, (GLenum)GLU_SMOOTH);
  gluSphere (quadObj, radius, slices, stacks);
  glPopMatrix();
}

void
SooSphere::setCenter(float x, float y, float z)
{
  center[0] = x;
  center[1] = y;
  center[2] = z;
  touch();
}

void
SooSphere::setCenter(double * c)
{
  center[0] = (float)c[0];
  center[1] = (float)c[1];
  center[2] = (float)c[2];
  touch();
}

void
SooSphere::getCenter(float &x, float &y, float &z)
{
  x = center[0];
  y = center[1];
  z = center[2];  
}

void
SooSphere::setRadius(float r)
{
  radius = r;
  touch();
}

float
SooSphere::getRadius()
{
  return radius;
}

void
SooSphere::setSlices(unsigned long r)
{
  slices = r;
  touch();
}

unsigned long
SooSphere::getSlices()
{
  return slices;
}

void
SooSphere::setStacks(unsigned long r)
{
  stacks = r;
  touch();
}

unsigned long
SooSphere::getStacks()
{
  return stacks;
}
