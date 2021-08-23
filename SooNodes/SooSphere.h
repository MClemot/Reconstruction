// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_SPHERE_H
#define __SOO_SPHERE_H

#include "SooDrawable.h"


class SooSphere : public SooDrawable {
public:
  float radius;
  float center[3];
  unsigned long slices;
  unsigned long stacks;

  /// Creates a sphere node with default settings.
  SooSphere();
  /// Creates a sphere with radius r and center = (x,y,z)
  SooSphere(float x, float y, float z, float r);
  SooSphere(float * c, float r);
  /// Destructor
  ~SooSphere() {}

  void by_default();
  void by_default(float x, float y, float z, float r);
  void draw();
  
  void setRadius(float r);
  float getRadius();
  void setCenter(float x, float y, float z);
  void setCenter(double * c);
  void getCenter(float &x, float &y, float &z);
  void setStacks(unsigned long r);
  unsigned long getStacks();
  void setSlices(unsigned long r);
  unsigned long getSlices();
};

#endif
