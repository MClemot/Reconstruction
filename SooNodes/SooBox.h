// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_BOX_H
#define __SOO_BOX_H

#include "SooDrawable.h"

// Dessine une boite dont les bords sont paralleles
// aux axes et allant du coin min au coin max

class SooBox : public SooDrawable
{
 private:
  GLenum type;
  float inf[3];
  float sup[3];
 public:
  SooBox();
  SooBox(float * a, float * b);
  
  void by_default();
  void draw();
  void setInfCorner(float x, float y, float z);
  void setSupCorner(float x, float y, float z);
  void getInfCorner(float &x, float &y, float &z);
  void getSupCorner(float &x, float &y, float &z);
};

#endif
