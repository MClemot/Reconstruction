#include "MiscMath.h"
#include "SooTriangles.h"

/** OpenGL instructions to draw a triangle */
void
glDraw(const Point_3 & a, const Point_3 & b, const Point_3 & c)
{
  Vector_3 normal;

  // Computing the normal to the triangle
  normal = unit_normal(a, b, c);
  glNormal3d(normal.x(), normal.y(), normal.z());

  // Drawing the triangle
  glBegin(GL_TRIANGLES);
  glVertex3d(a.x(),a.y(),a.z());
  glVertex3d(b.x(),b.y(),b.z());
  glVertex3d(c.x(),c.y(),c.z());
  glEnd();
}

/** OpenGL instructions to draw a triangle */
void
glDraw(const Triangle_3 & triangle)
{
  Vector_3 normal;

  // Computing the normal to the triangle
  normal = unit_normal(triangle.vertex(0),triangle.vertex(1),triangle.vertex(2));
  glNormal3d(normal.x(), normal.y(), normal.z());

  // Drawing the triangle
  glBegin(GL_TRIANGLES);
  for (int j = 0; j < 3; j++)
    glVertex3d(triangle.vertex(j).x(),triangle.vertex(j).y(),triangle.vertex(j).z());
  glEnd();
}

Point_3
SooTriangles::Centroid(int i)
{
  Point_3 a = (*vertices)[(*triangles)[i][0]];
  Point_3 b = (*vertices)[(*triangles)[i][1]];
  Point_3 c = (*vertices)[(*triangles)[i][2]];
  Point_3 m = CGAL::barycenter(a,1/3.0,b,1/3.0,c);
  return m;
}

void
SooTriangles::draw()
{
  if (*sort_first)
    {
      Vector_3 direction_camera = Point_3(camera[0], camera[1], camera[2]) - CGAL::ORIGIN;
      vector<INT_WEIGHTED> permutation;
      vector<vector<int>> triangles_sorted;
      int i;

      // First, we sort triangles by increasing distance to the camera
      for (i=0; i < (*triangles).size(); i++)
        permutation.push_back(INT_WEIGHTED(i, direction_camera * (Centroid(i) - CGAL::ORIGIN) ));
      std::sort (permutation.begin(), permutation.end(), COMPARISON_INT_WEIGHTED);

      // We draw triangles in the order given in the permutation
      for (vector<INT_WEIGHTED>::iterator p = permutation.begin() ; p != permutation.end() ; p++)
        {
          i=(*p).first;
          glDraw((*vertices)[(*triangles)[i][0]],(*vertices)[(*triangles)[i][1]],(*vertices)[(*triangles)[i][2]]);
        }
    }
  else
    for (vector<vector<int>>::iterator pt_triangle = triangles->begin(); pt_triangle != triangles->end(); pt_triangle++)
      glDraw((*vertices)[(*pt_triangle)[0]],(*vertices)[(*pt_triangle)[1]],(*vertices)[(*pt_triangle)[2]]);
}
