// (c) Dominique Attali 2003 (LIS)

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#ifndef _WIN32
#include <GL/glext.h>
#endif
#include "SooGroupColor.h"

SooGroupColor::SooGroupColor(SooDrawable * d) : SooGroupRender()
{
  offset = 1;

  // ----- DRAW STYLE
  drawstyle = new SooDrawStyle();
  addChild(drawstyle);

  // ----- COLOR
  color = new SooColor();
  addChild(color);

  // ----- DRAWABLE
  drawable = d;
  addChild(d);
}

void
SooGroupColor::drawbefore()
{
#ifdef GL_EXT_polygon_offset
  if (offset)
    glEnable(GL_POLYGON_OFFSET_EXT);
  else
    glDisable(GL_POLYGON_OFFSET_EXT);
#endif
}


