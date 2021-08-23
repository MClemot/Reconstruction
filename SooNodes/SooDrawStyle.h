// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_DRAW_STYLE_H
#define __SOO_DRAW_STYLE_H

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

#include "SooDrawable.h"

class SooDrawStyle : public SooDrawable
{
 private:
  float pointSize;		// Radius of points (for POINTS style)
  float lineWidth;		// Width of lines (for LINES style)
  unsigned short linePattern;	// Line pattern (for LINES style)
  int style;

 public:
  enum {
    FILLED=GL_FILL,		// Draw filled regions
    LINES=GL_LINE,              // Draw only lines (wire frame)
    POINTS=GL_POINT,		// Draw points at vertices
    INVISIBLE=0xff		// Do not draw anything at all
  };

  SooDrawStyle();
  void by_default();
  void draw();

  int getStyle();
  void setStyle(int);

  float getPointSize();
  void setPointSize(float);
  
  float getLineWidth();
  void setLineWidth(float);
  
  unsigned short getLinePattern();
  void setLinePattern(unsigned short);

  void printShort(ostream & o);
};

#endif
