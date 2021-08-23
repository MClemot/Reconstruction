// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_GLUT_MODEL_H
#define __SOO_GLUT_MODEL_H

#include "SooDrawable.h"

class SooGlutModel : public SooDrawable
{
 private:
  int type;
 public:
  enum {
    TORUS,
    TEAPOT,
    ICOSAHEDRON,
    DODECAHEDRON,
    CONE,
    CUBE,
    TETRAHEDRON,
    SPHERE
  };

  SooGlutModel(int t = TEAPOT);
  void by_default();

  void draw();
  void setType(int value);
  int getType();
};

#endif
