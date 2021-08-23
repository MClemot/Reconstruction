#include "MiscMath.h"
#include "SooTrianglesVar.h"

Point_3
SooTrianglesVar::Centroid(int i)
{
  Point_3 a = (*vertices)[(*triangles)[i][0]];
  Point_3 b = (*vertices)[(*triangles)[i][1]];
  Point_3 c = (*vertices)[(*triangles)[i][2]];
  Point_3 m = CGAL::barycenter(a,1/3.0,b,1/3.0,c);
  return m;
}

void
SooTrianglesVar::draw()
{
  if (*sort_first)
    {
      Vector_3 direction_camera = Point_3(camera[0], camera[1], camera[2]) - CGAL::ORIGIN;
      vector<INT_WEIGHTED> permutation;
      vector<vector<int>> triangles_sorted;
      int i;

      // First, we sort triangles by increasing distance to the camera
      for (i=0; i < (*triangles).size() && i < n; i++)
        permutation.push_back(INT_WEIGHTED(i, direction_camera * (Centroid(i) - CGAL::ORIGIN) ));
      std::sort (permutation.begin(), permutation.end(), COMPARISON_INT_WEIGHTED);

      // We draw triangles in the order given in the permutation
      for (vector<INT_WEIGHTED>::iterator p = permutation.begin() ; p != permutation.end() ; p++)
        {
          i=(*p).first;
          glDraw((*vertices)[(*triangles)[i][0]],(*vertices)[(*triangles)[i][1]],(*vertices)[(*triangles)[i][2]]);
        }
    }
  else {
      int i = 0;
      for (vector<vector<int>>::iterator pt_triangle = triangles->begin(); pt_triangle != triangles->end(); pt_triangle++) {
          if (i >= n)
              break;
          glDraw((*vertices)[(*pt_triangle)[0]], (*vertices)[(*pt_triangle)[1]], (*vertices)[(*pt_triangle)[2]]);
          i++;
      }
  }
}
