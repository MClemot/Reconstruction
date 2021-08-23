#ifndef __TYPES_TREE_H
#define __TYPES_TREE_H

#include <tuple>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Fuzzy_sphere.h>
#include <CGAL/Search_traits_3.h>
#include <CGAL/Orthogonal_k_neighbor_search.h>

typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_3 Point_3;
typedef K::Vector_3 Vector_3;
typedef K::Triangle_3 Triangle_3;
typedef K::FT FT;

// Item in the Kd-tree: position (Point_3) + index
class PointId_3 : public Point_3
{
public:
  unsigned int index;

  // basic geometric types
  typedef CGAL::Origin Origin;

  PointId_3(const Origin& o = CGAL::ORIGIN, unsigned int id=0)
    : Point_3(o), index(id)
  {}
  PointId_3(const Point_3& p, unsigned int id=0)
    : Point_3(p), index(id)
  {}
  PointId_3(const PointId_3& other)
    : Point_3(other), index(other.index)
  {}
};

// Helper class for the Kd-tree
class Kd_tree_gt : public K
{
public:
  typedef PointId_3 Point_3;
};


class Kd_tree_traits : public CGAL::Search_traits_3<Kd_tree_gt>
{
public:
  typedef Point_3 PointType;
};


//types for range search
typedef Kd_tree_traits Traits;
typedef CGAL::Kd_tree<Traits> Tree;
typedef CGAL::Fuzzy_sphere<Traits> Fuzzy_sphere;



#endif
