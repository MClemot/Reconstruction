// (c) Dominique Attali 2003 (LIS)

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#ifndef _WIN32
#include <GL/glext.h>
#endif
#include "SooGroupMaterial.h"

SooGroupMaterial::SooGroupMaterial(SooDrawable * d)
  : SooGroup("Group Material")
{
  drawable = d;

  // **********************************
  //
  //    NODE FILLED
  //
  // **********************************

  // ----- GROUP FILLED
  group_filled = new SooGroupRender();
  addChild(group_filled);

  // ----- DRAW FILLED
  drawstyle_filled = new SooDrawStyle();
  drawstyle_filled->setStyle(SooDrawStyle::FILLED);
  group_filled->addChild(drawstyle_filled);

  // ----- MATERIAL FILLED
  material_filled = new SooMaterial();
  material_filled->set(SooMaterial::TURQUOISE);
  group_filled->addChild(material_filled);

  // ----- COLOR FILLED
  color_filled = new SooColor();
  color_filled->set(1.0, 1.0, 1.0);
  group_filled->addChild(color_filled);

  // ----- NODE
  group_filled->addChild(drawable);

  // **********************************
  //
  //    NODE LINES
  //
  // **********************************

  // ----- GROUP LINES
  group_lines = new SooGroupRender();
  group_lines->setDepthMask(0);
  group_lines->setBlending(1);
  addChild(group_lines);

  // ----- MATERIAL LINES
  material_lines = new SooMaterial();
  material_lines->set(SooMaterial::OBSEDIAN);
  group_lines->addChild(material_lines);

  // ----- COLOR LINES
  color_lines = new SooColor();
  color_lines->set(0.0, 0.0, 0.0);
  group_lines->addChild(color_lines);

  // ----- DRAW LINES
  drawstyle_lines = new SooDrawStyle();
  drawstyle_lines->setStyle(SooDrawStyle::LINES);
  drawstyle_lines->setLineWidth(1.0);
  group_lines->addChild(drawstyle_lines);

  // ----- NODE LINES
  group_lines->addChild(drawable);

  set(FILLED_AND_LINES);
}

void
SooGroupMaterial::drawbefore()
{
#ifdef GL_EXT_polygon_offset
  if (offset)
    glEnable(GL_POLYGON_OFFSET_EXT);
  else
    glDisable(GL_POLYGON_OFFSET_EXT);
#endif
}

void
SooGroupMaterial::set(int gf, int cf, int mf,
    int gl, int cl, int ml,
    int useroffset)
{
  group_filled->setDisplay(gf);
  color_filled->setDisplay(cf);
  material_filled->setDisplay(mf);

  group_lines->setDisplay(gl);
  color_lines->setDisplay(cl);
  material_lines->setDisplay(ml);

  offset = useroffset;
}

void
SooGroupMaterial::set(int type)
{
  switch (type)
    {
    case WHITE: set(1,1,0,0,0,0,1); break;
    case LINES: set(0,1,0,1,0,1,1); break;
    case OUTLINES: set(1,1,0,1,1,0,1); break;
    case FILLED: set(1,0,1,0,0,0,1); break;
    case FILLED_AND_LINES: set(1,0,1,1,0,1,1); break;
    case FILLED_AND_OUTLINES: set(1,0,1,1,1,0,1); break;
    }
}
