// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_CIRCLE_H
#define __SOO_CIRCLE_H

#include "SooDrawable.h"

// Dessine un cercle de centre c et de rayon r, dans le plan defini
// par le repere (u,v)

class SooCircle : public SooDrawable {
private:
  double radius;
  double center[3];
  double axe[3];

 public:
  SooCircle();
  SooCircle(double * c, double r, double * a);

  void by_default();
  void draw();
  
  void setRadius(double r);
  double getRadius();
  void setCenter(double x, double y, double z);
  void getCenter(double &x, double &y, double &z);
  void setAxe(double x, double y, double z);
  void getAxe(double &x, double &y, double &z);
};

#endif
