#ifndef __ALGORITHMS_H
#define __ALGORITHMS_H

#include <iostream>
#include <random>

#include "types-cgal.h"

using namespace std;

extern void OffsetTriangle(Point_3 * a, double param);

extern void Write(ostream& o, vector<Point_3> & cloud);

extern bool Load(vector<Point_3> & cloud, const char * name);

extern bool Load(vector<Point_3> & vertices, vector<vector<int>> & triangles, const char * name);

extern double DistanceToNearest(vector<Point_3> & cloud, Point_3 & p);

#endif
