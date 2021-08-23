// (c) Dominique Attali 2003 (LIS)

#include "SooBox.h"

void
SooBox::by_default()
{
  type = GL_QUADS;
  setInfCorner(0.0,0.0,0.0);
  setSupCorner(1.0,1.0,1.0);  
}

SooBox::SooBox() : SooDrawable("Box")
{
  by_default();
}

SooBox::SooBox(float * a, float * b) : SooDrawable("Box")
{
  type = GL_QUADS;
  setInfCorner(a[0],a[1],a[2]);
  setSupCorner(b[0],b[1],b[2]);
}

void
SooBox::draw()
{
  if (type==GL_QUADS)
    {
      glBegin( GL_QUADS );
      glNormal3d(-1.0,0.0,0.0);
      glVertex3f(inf[0],inf[1],inf[2]);  glVertex3f(inf[0],sup[1],inf[2]);
      glVertex3f(inf[0],sup[1],sup[2]);  glVertex3f(inf[0],inf[1],sup[2]);
      
      glNormal3d(1.0,0.0,0.0);
      glVertex3f(sup[0],inf[1],inf[2]);  glVertex3f(sup[0],inf[1],sup[2]);
      glVertex3f(sup[0],sup[1],sup[2]);  glVertex3f(sup[0],sup[1],inf[2]);

      glNormal3d(0.0,1.0,0.0);
      glVertex3f(inf[0],sup[1],inf[2]);  glVertex3f(sup[0],sup[1],inf[2]);
      glVertex3f(sup[0],sup[1],sup[2]);  glVertex3f(inf[0],sup[1],sup[2]);
      
      glNormal3d(0.0,-1.0,0.0);
      glVertex3f(inf[0],inf[1],inf[2]);  glVertex3f(inf[0],inf[1],sup[2]);
      glVertex3f(sup[0],inf[1],sup[2]);  glVertex3f(sup[0],inf[1],inf[2]);
      
      glNormal3d(0.0,0.0,1.0);
      glVertex3f(inf[0],inf[1],sup[2]);  glVertex3f(inf[0],sup[1],sup[2]);
      glVertex3f(sup[0],sup[1],sup[2]);  glVertex3f(sup[0],inf[1],sup[2]);
      
      glNormal3d(0.0,0.0,-1.0);
      glVertex3f(inf[0],inf[1],inf[2]);  glVertex3f(sup[0],inf[1],inf[2]);
      glVertex3f(sup[0],sup[1],inf[2]);  glVertex3f(inf[0],sup[1],inf[2]);
      
      glEnd();
    }
  else
    {
      glBegin( GL_LINES );
      glVertex3d(inf[0],inf[1],inf[2]);glVertex3d(inf[0],inf[1],sup[2]);
      glVertex3d(inf[0],inf[1],inf[2]);glVertex3d(inf[0],sup[1],inf[2]);
      glVertex3d(inf[0],inf[1],inf[2]);glVertex3d(sup[0],inf[1],inf[2]);
      glVertex3d(sup[0],sup[1],sup[2]);glVertex3d(sup[0],sup[1],inf[2]);
      glVertex3d(sup[0],sup[1],sup[2]);glVertex3d(sup[0],inf[1],sup[2]);
      glVertex3d(sup[0],sup[1],sup[2]);glVertex3d(inf[0],sup[1],sup[2]);
      glVertex3d(inf[0],inf[1],sup[2]);glVertex3d(inf[0],sup[1],sup[2]);
      glVertex3d(inf[0],inf[1],sup[2]);glVertex3d(sup[0],inf[1],sup[2]);
      glVertex3d(inf[0],sup[1],inf[2]);glVertex3d(sup[0],sup[1],inf[2]);
      glVertex3d(inf[0],sup[1],inf[2]);glVertex3d(inf[0],sup[1],sup[2]);
      glVertex3d(sup[0],inf[1],inf[2]);glVertex3d(sup[0],sup[1],inf[2]);
      glVertex3d(sup[0],inf[1],inf[2]);glVertex3d(sup[0],inf[1],sup[2]);
      glEnd();
    }
}

void
SooBox::setInfCorner(float x, float y, float z)
{
  inf[0] = x;
  inf[1] = y;
  inf[2] = z;
  touch();
}

void
SooBox:: setSupCorner(float x, float y, float z)
{
  sup[0] = x;
  sup[1] = y;
  sup[2] = z;
  touch();
}

void
SooBox:: getInfCorner(float &x, float &y, float &z)
{
  x = inf[0];
  y = inf[1];
  z = inf[2];
}

void
SooBox:: getSupCorner(float &x, float &y, float &z)
{
  x = sup[0];
  y = sup[1];
  z = sup[2];
}
