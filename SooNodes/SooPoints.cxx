// (c) Dominique Attali 2003 (LIS)

#include "SooSphere.h"
#include "SooPoints.h"

// ================================================
//
//   C O N S T R U C T O R   -   D E S T R U C T O R   -  D E F A U L T
//
// ================================================

void
SooPoint::by_default()
{
  set(0.0, 0.0, 0.0);
}

SooPoint::SooPoint() : SooDrawable("Point")
{
  by_default();
}

SooPoint::SooPoint(double * c) : SooDrawable("Point")
{
  set(c);
}

SooPoint::SooPoint(double x, double y, double z) : SooDrawable("Point")
{
  set(x,y,z);
}

// ================================================
//
//   D R A W I N G
//
// ================================================

void
SooPoint::draw()
{
  glBegin(GL_POINTS);
  glVertex3dv(coordinates);
  glEnd();
}

// ================================================
//
//   S E T   -   G E T
//
// ================================================

void
SooPoint::set(double x, double y, double z)
{
  coordinates[0] = x;
  coordinates[1] = y;
  coordinates[2] = z;
  touch();
}

void
SooPoint::set(double * c)
{
  set(c[0], c[1], c[2]);
}

void
SooPoint::get(double *x, double *y, double *z)
{
  *x = coordinates[0];
  *y = coordinates[1];
  *z = coordinates[2];
}

void
SooPoint::get(double * c)
{
  c[0] = coordinates[0];
  c[1] = coordinates[1];
  c[2] = coordinates[2];
}




void SooPointCloudEmbellished::draw()
{
  CGAL::Simple_cartesian<double>::Point_3 p;
  double radius = (*param_size_spheres_cloud) * range->size();

  SooMaterial material_sphere;
  material_sphere.set(SooMaterial::GOLD);

  glFrontFace(GL_CCW);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  material_sphere.draw();
  for (int i = 0; i < cloud->size(); i++)
    {
      p = (*cloud)[i];
      SooSphere sphere(p.x(), p.y(), p.z(), radius);
      glPushName(i);
      sphere.draw();
      glPopName();
    }
}
