#include <stdio.h>
#include <math.h>

#include "Misc.h"
#include "SooAxes.h"
#include "demo-axes-Scene.h"

Scene::Scene()
{
  // ----- ROOT
  root = new SooGroupRender();

  // **********************************
  //
  //    AXES
  //
  // **********************************

  group_axes =  new SooGroupColor(new SooAxes());
  group_axes->drawstyle->setStyle(SooDrawStyle::LINES);
  group_axes->drawstyle->setLineWidth(1.5);
  group_axes->color->set(0.0, 0.0, 1.0);
  group_axes->setDisplay(1);
  root->addChild(group_axes);

  root->printTree();
}

Scene::~Scene()
{
  delete root;
}

// *****************************************************
// 
//   U P D A T E   W I T H   C H A N G I N G   C A M E R A
//
// *****************************************************

void
Scene::UpdateWithCamera()
{
}

// *****************************************************
// 
//   R E N D E R
//
// *****************************************************

void
Scene::render()
{
  root->render();
}

// *****************************************************
// 
//   P R O C E S S   A   C L I C K
//
// *****************************************************

int
Scene::process(SooNode * selection, double * click, int number, set<int> & set_elements)
{
  return 0;
}
