// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_GROUP_MATERIAL_H
#define __SOO_GROUP_MATERIAL_H

#include "SooDrawable.h"
#include "SooGroup.h"
#include "SooGroupRender.h"
#include "SooColor.h"
#include "SooMaterial.h"
#include "SooDrawStyle.h"
#include "SooDrawable.h"

// Forme un groupe

class SooGroupMaterial : public SooGroup
{
 public:
  enum{ OUTLINES, LINES, FILLED, FILLED_AND_LINES, FILLED_AND_OUTLINES, WHITE
  };
  int offset;

  // ----- Surface filled properties
  SooGroup * group_filled;
  SooDrawStyle * drawstyle_filled;
  SooMaterial * material_filled;
  SooColor * color_filled;

  // ----- Surface lines properties
  SooGroupRender * group_lines;
  SooDrawStyle * drawstyle_lines;
  SooMaterial * material_lines;
  SooColor * color_lines;

  // ----- Drawable
  SooDrawable * drawable;

  SooGroupMaterial(SooDrawable * d);

  inline void touch() { drawable->touch(); }

  void set(int gf, int cf, int mf,
      int gl, int cl, int ml,
      int offset);

  void set(int);
  void drawbefore();
};

#endif


