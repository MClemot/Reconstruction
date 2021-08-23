// (c) Dominique Attali 2015 (Gipsa-lab)

#ifndef __RANGE_H
#define __RANGE_H

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

#include "types-cgal.h"

using namespace std;

class Range {
 private:
  Point_3 min, max;

 public:
  Range() { cout << "constructeur Range" << endl; SetDefault(); }

  inline void Set(double x, double y, double z, double w, double h, double k)
  {
    min = Point_3(x,y,z);
    max = Point_3(x+w,y+h,z+k);
  }

  inline void SetDefault() { Set(-1, -1, -1, 2, 2, 2); }

  inline void Set(Point_3 c, double r)
  {
    Vector_3 v = Vector_3(r,r,r);
    min = c-v;
    max = c+v;
  }

  void BoundingBox(vector<Point_3> & cloud);
  void BoundingBox(vector<PointId_3> & cloud);

  void Squaring();
  void Scaling(double s);
  void Translating(Point_3 & p);
  
  double size();
  Point_3 center();

  friend ostream & operator << (ostream & o, Range & range);
};

#endif
