// (c) Dominique Attali 2015 (Gipsa-lab)

#ifndef __SOO_PALETTE_H
#define __SOO_PALETTE_H

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#include "SooMaterial.h"
#include "SooColor.h"

using namespace std;

class SooPaletteColor {
 private:
  float	color[3];
  
 public:
  SooPaletteColor();
  SooPaletteColor(float red, float green, float blue)
    { set(red, green, blue); }

  void set(float * rgb)
  {
    color[0] = rgb[0];
    color[1] = rgb[1];
    color[2] = rgb[2];
  }

  void set(float red, float green, float blue)
  {
    color[0] = red;
    color[1] = green;
    color[2] = blue;
  }

  void get(float &red, float &green, float &blue)
  {
    red = color[0];
    green = color[1];
    blue = color[2];
  }
  
  float red() { return color[0]; }
  float green() { return color[1]; }
  float blue() { return color[2]; }

  friend ostream & operator << (ostream & o, SooPaletteColor & color)
    {
      o << color.red() << " " << color.green() << " " << color.blue();
      return o;
    }
};

class SooPalette
{
 private:
  vector<SooPaletteColor> lut;
  
 public:
  bool Load(const char * name);
  void Print();
  SooMaterial Material(double x, double transparency);
  SooColor Color(double x);
};

#endif
