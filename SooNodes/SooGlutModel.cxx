// (c) Dominique Attali 2003 (LIS)

#include <stdio.h>
#include <math.h>
#include <FL/glut.H>
#include "SooGlutModel.h"

void
SooGlutModel::by_default()
{
  setType(TEAPOT);
}

SooGlutModel::SooGlutModel(int t) : SooDrawable("GlutModel")
{
  by_default();
}

void
SooGlutModel::setType(int t)
{
  type = t;
  touch();
}

int
SooGlutModel::getType()
{
  return type;
}

void
SooGlutModel::draw()
{
#if 0
  glFrontFace(GL_CW);
  switch (type)
    {
    case TEAPOT:
      glPushMatrix();
      glRotatef(90.0, 1.0, 0.0, 0.0);
      glutSolidTeapot(0.5);
      glPopMatrix();
      break;
    case TORUS:
      glFrontFace(GL_CCW);
      glutSolidTorus (0.275, 0.85, 15, 15);
      break;
    case ICOSAHEDRON:
      glPushMatrix();
      glScalef(0.5,0.5,0.5);
      glutSolidIcosahedron();
      glDisable(GL_LIGHTING);
      glColor3f(0.0, 0.0, 0.0);
      glutWireIcosahedron();
      glPopMatrix();
      break;
    case DODECAHEDRON:
      glPushMatrix();
      glScalef(0.5,0.5,0.5);
      glutSolidDodecahedron();
      glDisable(GL_LIGHTING);
      glColor3f(0.0, 0.0, 0.0);
      glutWireDodecahedron();
      glPopMatrix();
      break;
    case CONE:
      glFrontFace(GL_CCW);
      glutSolidCone(1.0, 1.0, 40, 40);
      break;
    case CUBE:
      glutSolidCube(2.0);
      break;
    case SPHERE:
      glFrontFace(GL_CCW);
      glutSolidSphere(1.0,10,10);
      break;
    case TETRAHEDRON:
      glutSolidTetrahedron();
      break;
    }
#endif
}
