// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_SWITCH_H
#define __SOO_SWITCH_H

#include <iostream>
#include <map>
#include "SooNode.h"

using namespace std;


class SooSwitch : public SooNode
{
protected:
  std::map<int, SooNode *> map_nodes;
  int * child_to_draw;

 public:
 SooSwitch(int * c) : SooNode("Switch") { child_to_draw = c; }
 SooSwitch(int * c, string n) : SooNode(n) { child_to_draw = c; };
  ~SooSwitch();
  virtual void drawbefore() {}

  void touch();
  void render();
  void addChild(int d, SooNode * child);
  void removeChild(SooNode * child);
  void removeAllChildren();
  virtual void printSubTree(int n);
};

#endif
