// (c) Dominique Attali 2015 (Gipsa-lab)

#include "MiscMath.h"
#include "Range.h"

void Range::BoundingBox(vector<Point_3> & cloud)
{
  CGAL::Bbox_3 bb = bbox_3(cloud.begin(), cloud.end());
  Point_3 a(bb.xmax(), bb.ymax(), bb.zmax());
  Point_3 b(bb.xmin(), bb.ymin(), bb.zmin());
  min = b;
  max = a;
}

void Range::BoundingBox(vector<PointId_3> & cloud)
{
  CGAL::Bbox_3 bb = bbox_3(cloud.begin(), cloud.end());
  Point_3 a(bb.xmax(), bb.ymax(), bb.zmax());
  Point_3 b(bb.xmin(), bb.ymin(), bb.zmin());
  min = b;
  max = a;
}

void Range::Squaring()
{
  Set(center(),size());
}

void Range::Scaling(double s)
{
  Vector_3 v = (max-min)/2.0;
  Point_3 center = min + v;
  max = center + s*v;
  min = center - s*v;
}

void Range::Translating(Point_3 & p)
{
  Vector_3 t = p - CGAL::ORIGIN;
  max = max + t;
  min = min + t;
}

Point_3 Range::center()
{
  return min + (max-min)/2.0;
}

double Range::size()
{
  Point_3 c = center();
  return sqrt( squared_distance(min,c) );
}

ostream & operator << (ostream & o, Range & range)
{
  o << "Range : " << endl << endl;
   
  o << "                                       " << range.max << endl;
  o << "                ---------------------------- " << endl;
  o << "               /|                         /| " << endl;
  o << "              /------------------------- / | " << endl;
  o << "             |  |                       |  | " << endl;
  o << "             |  |                       |  | " << endl;
  o << "             |  |                       |  | " << endl;
  o << "             |  |-----------------------|--| " << endl;
  o << "             | /                        | /  " << endl;
  o << "             |/-------------------------|/   " << endl;
  o << " " << range.min << endl;

  return o;
}
