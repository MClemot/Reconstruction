#ifndef __SOO_TRIANGLES_H
#define __SOO_TRIANGLES_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <FL/gl.h>
#include <FL/glu.h>

#include <vector>

#include "SooDrawable.h"
#include "SooMaterial.h"
#include "types-cgal.h"

extern void glDraw(const Triangle_3 & triangle);
extern void glDraw(const Point_3 & a, const Point_3 & b, const Point_3 & c);

class SooTriangles : public SooDrawable
{
 public:
  vector<Point_3> * vertices;      // Vector of vertices
  vector<vector<int>> * triangles; // Vector of triangles
  bool * sort_first;  // Should triangles be sorted before being drawn
  double * camera;

 SooTriangles(vector<Point_3> * vertices, vector<vector<int>> * triangles, bool * sort_first, double * camera)
   : SooDrawable("Triangles"), vertices(vertices), triangles(triangles), sort_first(sort_first), camera(camera) { }

  /** OpenGL instructions to draw the triangles */
  void draw();

  /** Returns the centroid of the ith triangle. If the triangle has
      vertices (abc), the centroid will be the point 1/3(a+b+c) */
  Point_3 Centroid(int i);
};


#endif
