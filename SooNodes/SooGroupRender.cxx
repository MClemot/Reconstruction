// (c) Dominique Attali 2003 (LIS)

#include <stdio.h>
#include "SooGroupRender.h"

void
SooGroupRender::by_default()
{
  setBlending(1);
  setDepthMask(1);
}

SooGroupRender::SooGroupRender() : SooGroup("GroupRender")
{
  by_default();
}

SooGroupRender::SooGroupRender(int b, int d) : SooGroup("GroupRender")
{
  setBlending(b);
  setDepthMask(d);
}

void
SooGroupRender::render()
{

  glPushAttrib(GL_DEPTH_BUFFER_BIT);
  glPushAttrib(GL_COLOR_BUFFER_BIT);

  glDepthMask(depth_mask?GL_TRUE:GL_FALSE);

  if (blending)
    glEnable(GL_BLEND);
  else
    glDisable(GL_BLEND);

  SooGroup::render();

  glPopAttrib( );
  glPopAttrib( );
}

void
SooGroupRender::printShort(ostream& o)
{
  o << getName();

  if (!getDisplay()) {o << "--"; return; }

  o << " (";

  if (blending)
    o << "blending / ";
  else
    o << "no blending / ";

  if (depth_mask)
    o << "depth";
  else
    o << "no depth";
  o << ")";
}

void
SooGroupRender::setBlending(int b)
{
  blending = b;
}

int
SooGroupRender::getBlending()
{
  return blending;
}

void
SooGroupRender::setDepthMask(int d)
{
  depth_mask = d;
}

int
SooGroupRender::getDepthMask()
{
  return depth_mask;
}
