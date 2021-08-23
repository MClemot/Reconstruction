// (c) Dominique Attali 2003 (LIS)

#include <cstdio>
#include <iostream>
#include <string>
#include "SooNode.h"

SooNode * 
findPtrSooNode(GLuint key)
{
  MapPtrSooNode::iterator iter = SooNode::map.find(key);

  if (iter != SooNode::map.end())
    return (*iter).second;
  else
    return NULL;
}


//! Create a SooNode having name n
SooNode::SooNode(const string n)
{
  setName(n);
  display = 1;
  key = key_max;
  map.insert(MapPtrSooNode::value_type(key,this));
  key_max++;

#ifdef DEBUG
  cout << "SooNode::SooNode - name = " << n << " / key = " << key << endl;
#endif
}

//! Set the name of SooNode to n
void
SooNode::setName(const string n)
{
  name = n;
  //  strcpy(name,n);
}

//! Return the name of SooNode
string
SooNode::getName()
{
  return name;
}

void
SooNode::printShort(ostream &o)
{
  o << getName();
  if (!getDisplay()) {o << "--"; return; }
}

//! Display the SooNode in text mode
void
SooNode::printSubTree(int n)

{
  printShort(cout); cout << endl;
}

void
SooNode::printTree()
{
  int n = 4;
  cout<<endl<<string(n,' '); printSubTree(n+1); cout<<endl;
}

ostream& operator << (ostream& o, const SooNode & node)
{
  if (node.display)
    o << " " << node.name;
  return o;
}


//! Set the display status of the SooNode
void
SooNode::setDisplay(int d)
{
  display = d;
}

//! Change the display status of the SooNode
void
SooNode::changeDisplay()
{
  display = !display;
}

//! Return the display status of the SooNode
int
SooNode::getDisplay()
{
  return display;
}
