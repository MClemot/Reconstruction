// (c) Dominique Attali 2003 (LIS)

#include <stdio.h>
#include <iostream>
#include <string>
#include "SooGroup.h"

using namespace std;

SooGroup::SooGroup(string n) : SooNode(n)
{
  by_default();
}

SooGroup::SooGroup() : SooNode("Group")
{
  by_default();
}

SooGroup::~SooGroup()
{
  removeAllChildren();
}

void
SooGroup::by_default()
{
}

void
SooGroup::render()
{
  if (!getDisplay()) return;

  drawbefore();
  list<SooNode *>::iterator node;
  for (node = nodes.begin(); node!= nodes.end(); node++)
    (*node)->render();
}

void
SooGroup::addChild(SooNode * child)
{
  nodes.push_back(child);
}

void
SooGroup::removeChild(SooNode * child)
{
  printf("removeChild not implemented\n");
  //  nodes.erase(child);
}

void
SooGroup::removeAllChildren()
{
  nodes.clear();
}

void
SooGroup::printSubTree(int n)
{
  list<SooNode *>::iterator node;

  printShort(cout); cout << endl;
  for (node = nodes.begin(); node!= nodes.end(); node++)
    {
      cout << string(n, ' ') << "|______ "; fflush(stdout);
      (*node)->printSubTree(n+9);
    }
}

