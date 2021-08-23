// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_COLOR_H
#define __SOO_COLOR_H

#include <cstdio>
#include <iostream>
#include <string>
#include <FL/glu.h>
#include "SooDrawable.h"

using namespace std;

// Implemente une couleur OpenGL

class SooColor : public SooDrawable {
 private:
  float	color[3];
  
 public:
  SooColor();
 SooColor(float red, float green, float blue) : SooDrawable("Color")
    { set(red, green, blue); }

  void by_default();
  void draw();
  void print();
  void printShort(ostream & o);

  void set(float * rgb);
  void set(float red, float green, float blue);
  void get(float &red, float &green, float &blue);
  
  float red() { return color[0]; }
  float green() { return color[1]; }
  float blue() { return color[2]; }

  friend ostream & operator << (ostream & o, SooColor & color)
    {
      o << color.red() << " " << color.green() << " " << color.blue();
      return o;
    }
};

#endif

