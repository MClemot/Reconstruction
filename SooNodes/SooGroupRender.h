// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_GROUP_RENDER_H
#define __SOO_GROUP_RENDER_H

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

#include "SooGroup.h"

class SooGroupRender : public SooGroup
{
private:
  int blending;
  int depth_mask;

 public:
  SooGroupRender();
  SooGroupRender(int b, int d);
  void by_default();

  void render();
  void printShort(ostream& o);

  void setBlending(int type);
  int getBlending();
  void setDepthMask(int type);
  int getDepthMask();
};

#endif
