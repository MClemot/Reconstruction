// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_AXES_H
#define __SOO_AXES_H

#include "SooDrawable.h"

// Dessine un repere centre en (0,0,0).
// dont les 3 axes sont materialises par
// 3 segments de longueurs e
// Une lettre est dessinee a l'extremite de chaque segment

class SooAxes : public SooDrawable
{
 private:
  double size;
 public:
  SooAxes();
  void by_default();
  void draw();
  void setUnit(double );
  double getUnit();
};

#endif
