#include "GLScene.h"

// *****************************************************
// 
//   C O M P U T E   C A M E R A   P O S I T I O N
//
// *****************************************************

void GLScene::PrintCameraPosition()
{
  cout << camera_position[0] << " " << camera_position[1] << " " << camera_position[2] << endl;
}

void GLScene::PrintRange()
{
  cout << range << endl;
}

void
GLScene::DoTransform()
{
  Point_3 c = range.center();
  double s = 0.5*range.size();
  glScalef(1.0/s, 1.0/s, 1.0/s);
  glTranslatef(-c.x(), -c.y(), -c.z());
}

void
GLScene::zoom(int v)
{
  if (v>0)
    range.Scaling(0.95);
  else
    range.Scaling(1.0/0.95);
}

void
GLScene::translate(double x, double y, double z)
{
  Point_3 p(x,y,z);
  range.Translating(p);
}
