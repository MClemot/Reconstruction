#ifndef __GL_SCENE_H
#define __GL_SCENE_H

#include <set>
#include <iostream>
#include "SooNode.h"
#include "Range.h"

using std::cout;
using std::endl;

class GLScene
{
 protected:
  Range range;
  double camera_position[3];
 public:
  virtual void render() = 0;
  virtual int process(SooNode * selection, double * click, int element, set<int> & set_elements) = 0;
  virtual void UpdateWithCamera() = 0;
  void translate(double x, double y, double z);
  void zoom(int factor);
  void DoTransform();
  void PrintCameraPosition();
  void PrintRange();

  friend class GLViewer;
};

#endif
