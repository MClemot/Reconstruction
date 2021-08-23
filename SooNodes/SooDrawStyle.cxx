// (c) Dominique Attali 2003 (LIS)

#include "SooDrawStyle.h"

void
SooDrawStyle::by_default()
{
  setStyle(FILLED);
  setPointSize(0.);
  setLineWidth(0.);
  setLinePattern(0xFFFF);
}

void
SooDrawStyle::draw()
{
  glPolygonMode(GL_FRONT_AND_BACK, (GLenum)style);
#if 1
  if (style==LINES) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1,linePattern);
  }
#endif
  if(lineWidth>0.) glLineWidth(lineWidth);
  if(pointSize>0.) glPointSize(pointSize);
}

SooDrawStyle::SooDrawStyle() : SooDrawable("DrawStyle")
{
  by_default();
}

int
SooDrawStyle::getStyle()
{
  return style;
}

void
SooDrawStyle::setStyle(int s)
{
  style = s;
  touch();
}

float
SooDrawStyle::getPointSize()
{
  return pointSize;
}

void
SooDrawStyle::setPointSize(float s)
{
  pointSize = s;
  touch();
}
  
float
SooDrawStyle::getLineWidth()
{
  return lineWidth;
}

void
SooDrawStyle::setLineWidth(float l)
{
  lineWidth = l;
  touch();
}

unsigned short
SooDrawStyle::getLinePattern()
{
  return linePattern;
}

void
SooDrawStyle::setLinePattern(unsigned short p)
{
  linePattern = p;
  touch();
}

void
SooDrawStyle::printShort(ostream & o)
{
  o << getName();
  if (!getDisplay()) {o << "--"; return; }
  switch (style)
    {
    case FILLED: o << " FILLED"; break;
    case LINES: o << " LINES " << lineWidth; break;
    case POINTS: o << " POINTS " << pointSize; break;
    case INVISIBLE: o << " INVISIBLE"; break;
    }
}

