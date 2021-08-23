#ifndef __SOO_POINTS_H
#define __SOO_POINTS_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <FL/gl.h>
#include <FL/glu.h>

#include <queue>
#include <vector>

#include "SooDrawable.h"
#include "SooMaterial.h"
#include "types-cgal.h"
#include "Range.h"

// Dessine un point

class SooPoint : public SooDrawable
{
private:
  double coordinates[3];
public:
  SooPoint();
  SooPoint(double * c);
  SooPoint(double x, double y, double z);

  void by_default();
  void draw();

  void set(double x, double y, double z);
  void set(double * c);
  void get(double *x, double *y, double *z);
  void get(double * c);
};


class SooPoint3Ptr : public SooDrawable
{
private:
  Point_3 ** point;
public:
  SooPoint3Ptr(Point_3 ** point)
    : SooDrawable("Selected point"), point(point) {}

  void draw()
  {
    if (*point)
      {
        glBegin(GL_POINTS);
        glVertex3d((*point)->x(),(*point)->y(),(*point)->z());
        glEnd();
      }
  }
};


class SooPointIdPtr : public SooDrawable
{
public:
  PointId_3 ** point;

  SooPointIdPtr(PointId_3 ** point)
    : SooDrawable("Selected point"), point(point) {}

  void draw()
  {
    if (*point)
      {
        glBegin(GL_POINTS);
        glVertex3d((*point)->x(),(*point)->y(),(*point)->z());
        glEnd();
      }
  }
};

class SooPointCloud : public SooDrawable
{
 public:
  vector<Point_3> * cloud;
  double * point_size;

 SooPointCloud(vector<Point_3> * cloud, double * point_size = NULL)
   : SooDrawable("3D Point Cloud"), cloud(cloud), point_size(point_size) { }

  void draw()
  {
    Point_3 p;
    vector<Point_3>::iterator iter;

    if (point_size) glPointSize(*point_size);

    iter = cloud->begin();

    for (int i = 0; i < cloud->size(); i++)
      {
        glPushName(i);
        glBegin(GL_POINTS);
        p = (*cloud)[i];
        glVertex3d(p.x(),p.y(),p.z());
        glEnd();
        glPopName();
      }
  }
};


class SooPointIdCloud : public SooDrawable
{
public:
  vector<PointId_3> * cloud;
  SooPointIdCloud(std::vector<PointId_3> * cloud)
    : SooDrawable("Vector<PointId_3>"), cloud(cloud) {}

  void draw()
  {
    Point_3 p;
    vector<PointId_3>::iterator iter;
    iter = cloud->begin();

    glBegin(GL_POINTS);
    for (; iter != cloud->end(); iter++)
      {
        p = *iter;
        glVertex3d(p.x(),p.y(),p.z());
      }
    glEnd();
  }
};


class SooPointCloudEmbellished : public SooDrawable
{
 public:
  vector<Point_3> * cloud;
  double * param_size_spheres_cloud;
  Range * range;

 SooPointCloudEmbellished(vector<Point_3> * cloud, double * param_size_spheres_cloud, Range * range)
   : SooDrawable("3D Point Cloud"),
    cloud(cloud), param_size_spheres_cloud(param_size_spheres_cloud), range(range) { }

  void draw();
};



#endif
