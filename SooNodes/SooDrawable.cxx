// (c) Dominique Attali 2003 (LIS)

#include <cstdio>
#include <iostream>
#ifndef _WIN32
#include <strings.h>
#endif
#include <cmath>
#include "SooDrawable.h"

int SooDrawable::listIndex = 1;

// ================================================
//
// C O N S T R U C T E U R   D E   L A   C L A S S E   D R A W A B L E
//
// ================================================

// Par defaut, la liste est affichee
SooDrawable::SooDrawable(const string n) : SooNode(n)
{
  touch();
  list = listIndex;
  listIndex++;
}

// ================================================
//
// D E S T R U C T E U R   D E   L A   C L A S S E   D R A W A B L E
//
// ================================================

SooDrawable::~SooDrawable()
{
  glDeleteLists(list,1);
}

// ================================================
//
// R E N D E R
//
// ================================================

void
SooDrawable::render()
{
  if (!getDisplay()) return;

  if (must_be_updated)
    {
      glDeleteLists(list,1);
      glNewList(list,GL_COMPILE);
      glLoadName(key);

      draw();
      glEndList();
      must_be_updated = 0;
    }
  glCallList(list);
}

// ================================================
//
// A F F I C H A G E   E N   M O D E   T E X T E
//
// ================================================

void
SooDrawable::print()
{
  if (getDisplay())
    cout << "o " << getName() << endl;
}

// ================================================
//
// M O D I F I C A T I O N   D E S   P A R A M ET R E S
//
// ================================================

void
SooDrawable::touch()
{
  must_be_updated = 1;
}
