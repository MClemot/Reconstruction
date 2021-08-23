// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_GROUP_COLOR_H
#define __SOO_GROUP_COLOR_H

#include "SooGroupRender.h"
#include "SooColor.h"
#include "SooDrawStyle.h"
#include "SooDrawable.h"

// Forme un groupe

class SooGroupColor : public SooGroupRender
{
 public:
  int offset;
  SooDrawStyle * drawstyle;
  SooColor * color;
  SooDrawable * drawable;

  SooGroupColor(SooDrawable * d);
  inline void touch() { drawable->touch(); }
  void drawbefore();
};

#endif
