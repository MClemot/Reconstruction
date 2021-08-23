#include "SooRadiusSpheres.h"

void SooRadiusSpheres::draw() {
    CGAL::Simple_cartesian<double>::Point_3 p;

    SooMaterial material_sphere;
    material_sphere.set(SooMaterial::GOLD);

    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    material_sphere.draw();
    for (int i = 0; i < cloud->size(); i++)
    {
        p = (*cloud)[i];
        SooSphere sphere(p.x(), p.y(), p.z(), sqrt((*radii)[i]) * *factor);
        glPushName(i);
        sphere.draw();
        glPopName();
    }
}