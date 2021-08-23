// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_GROUP_H
#define __SOO_GROUP_H

#include <list>

using namespace std;

#include "SooNode.h"

class SooGroup : public SooNode
{
protected:
  list<SooNode *> nodes;
 public:
  SooGroup();
  SooGroup(string n);
  ~SooGroup();
  virtual void by_default();
  virtual void drawbefore() {}

  void render();
  void addChild(SooNode * child);
  void removeChild(SooNode * child);
  void removeAllChildren();
  virtual void printSubTree(int n);
};

#endif


