// (c) Dominique Attali 2003 (LIS)

#include <stdio.h>
#include "SooColor.h"

// ------------------------------------------------------------
void
SooColor::by_default()
{
  set(0.8, 0.8, 0.8);
}
 
// ------------------------------------------------------------
SooColor::SooColor() : SooDrawable("Color")
{
  by_default();
}

// ------------------------------------------------------------
void
SooColor::draw()
{
  glDisable(GL_LIGHTING);
  glColor3fv(color);
}

// ------------------------------------------------------------
void
SooColor::set(float red, float green, float blue)
{
  color[0] = red;
  color[1] = green;
  color[2] = blue;
  touch();
}

// ------------------------------------------------------------
void
SooColor::set(float * rgb)
{
  color[0] = rgb[0];
  color[1] = rgb[1];
  color[2] = rgb[2];
  touch();
}

// ------------------------------------------------------------
void
SooColor::get(float &red, float &green, float &blue)
{
  red = color[0];
  green = color[1];
  blue = color[2];
}

// ------------------------------------------------------------
void
SooColor::print()
{
  printf("Color  = (%lf, %lf, %lf)\n", color[0], color[1], color[2]);
}

void
SooColor::printShort(ostream & o)
{
  o << getName();

  if (!getDisplay()) {o << "--"; return; }

  o << " " << color[0] << " " << color[1] << " " << color[2];
}
