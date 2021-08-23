#ifndef __SOO_RADIUS_SPHERES_H
#define __SOO_RADIUS_SPHERES_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <FL/gl.h>
#include <FL/glu.h>

#include <vector>

#include "SooDrawable.h"
#include "SooMaterial.h"
#include "types-cgal.h"
#include "Range.h"
#include "SooSphere.h"

class SooRadiusSpheres : public SooDrawable
{
public:
    vector<Point_3>* cloud;
    vector<double>* radii;
    double* factor;

    SooRadiusSpheres(vector<Point_3>* cloud, vector<double>* radii, double* factor) : SooDrawable("3D Point Cloud"), cloud(cloud), radii(radii), factor(factor) { }

    void draw();
};

#endif
