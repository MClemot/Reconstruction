#ifndef __SCENE_H
#define __SCENE_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <FL/gl.h>
#include <FL/glu.h>

#include <queue>
#include <vector>

#include "SooGroupRender.h"
#include "SooGroupColor.h"
#include "GLScene.h"

class UserInterface;

// Classe permettant de gerer une scene 3D.
// La scene comporte une camera, une lumiere
// et un ensemble d'objets dont on sait
// comment les afficher a l'aide d'une liste OpenGL

class Scene : public GLScene
{
 public:
  // ****************************************************
  //
  //    SOO NODES
  //
  // ****************************************************

  // ----- Root
  SooGroupRender * root;

  // ----- Axis
  SooGroupColor * group_axes;

  // ----- 3D Point Cloud
  SooGroupColor * group_cloud;

  UserInterface * ui;

  /** Scene constructor */
  Scene();

  /** Scene destructor */
  ~Scene();

  void render();
  int process(SooNode * selection, double * click, int element, set<int> & set_elements);
  void UpdateWithCamera();
};

#endif
