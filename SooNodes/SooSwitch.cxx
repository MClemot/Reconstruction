// (c) Dominique Attali 2003 (LIS)

#include <stdio.h>
#include <iostream>
#include <string>
#include "SooSwitch.h"

using namespace std;

SooSwitch::~SooSwitch()
{
  removeAllChildren();
}

void
SooSwitch::render()
{
  if (!getDisplay()) return;

  drawbefore();
  
  std::map<int,SooNode *>::iterator it = map_nodes.find(*child_to_draw);
  if (it != map_nodes.end())
    it->second->render();
}

void
SooSwitch::addChild(int d, SooNode * child)
{
  map_nodes[d]=child;
}

void
SooSwitch::removeChild(SooNode * child)
{
  printf("removeChild not implemented\n");
  //  nodes.erase(child);
}

void
SooSwitch::removeAllChildren()
{
  map_nodes.clear();
}

void
SooSwitch::printSubTree(int n)
{
  SooNode * node;
  std::map<int,SooNode *>::iterator it = map_nodes.find(*child_to_draw);
  if (it != map_nodes.end())
    {
      node = it->second;
      printShort(cout); cout << endl;
      cout << string(n, ' ') << "|______ "; fflush(stdout);
      node->printSubTree(n+9);
    }
}

void
SooSwitch::touch()
{
  for (std::map<int,SooNode *>::iterator it=map_nodes.begin(); it!=map_nodes.end(); ++it)
    it->second->touch();
}
