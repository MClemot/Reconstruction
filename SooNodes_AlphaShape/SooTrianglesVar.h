#ifndef __SOO_TRIANGLESVAR_H
#define __SOO_TRIANGLESVAR_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <FL/gl.h>
#include <FL/glu.h>

#include <vector>

#include "SooDrawable.h"
#include "SooMaterial.h"
#include "types-cgal.h"

#include <SooTriangles.h>

class SooTrianglesVar : public SooDrawable
{
 public:
  vector<Point_3> * vertices;      // Vector of vertices
  vector<vector<int>> * triangles; // Vector of triangles
  bool * sort_first;  // Should triangles be sorted before being drawn
  double * camera;
  int n;

  SooTrianglesVar(vector<Point_3> * vertices, vector<vector<int>> * triangles, bool * sort_first, double * camera)
   : SooDrawable("Triangles"), vertices(vertices), triangles(triangles), sort_first(sort_first), camera(camera), n(0) { }

  /** OpenGL instructions to draw the triangles */
  void draw();

  /** Returns the centroid of the ith triangle. If the triangle has
      vertices (abc), the centroid will be the point 1/3(a+b+c) */
  Point_3 Centroid(int i);
};


#endif
