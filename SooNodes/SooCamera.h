// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_CAMERA_H
#define __SOO_CAMERA_H

#include "SooNode.h"

// Classe implementant une camera a l'aide d'instructions OpenGL
//
// La camera que l'on definit ici permet de tourner et de zoomer
// autour d'objets centres sur le point `target'.  La camera voit
// uniquement les objets dans un cone d'angle d'ouverture
// `field_of_view' et tronque par les plans de position `z_near' et
// `z_far'.
//
//
//            camera   clipping                            clipping       
//           position    plane           target             plane
//     __________|________|________|________|________|________|___________
//
//               |--------> z_near
//
//               |--------------------------------------------> z_far
//
//                                       '
//                                   '
//                               '
//                           ' \
//                       '      |    field_of_view
//            camera '          | 
//     __________|______________|__________________________________________
//                              |
//                   `          |
//                       `      |
//                           ` /
//                               `
//                                   `
//                                       `

class SooCamera : public SooNode {
 private:
  GLfloat position[3];		// Position initiale de la camera
  GLfloat target[3];		// Vers ou la camera pointe
  GLfloat up[3];		// Vecteur de projection verticale
  GLfloat field_of_view;	// Angle d'ouverture de la camera
  GLfloat aspect_ratio;		// Deformation entre l'horizontale et la verticale
  GLfloat z_near;		// La camera ne voit pas avant z_near
  GLfloat z_far;		// La camera ne voit pas au dela de z_far
  int initialized;

  // Position relative de la camera par rapport a la position initiale
  // donnee en coordonnees spheriques
  GLfloat alpha;
  GLfloat beta;
  GLfloat zoom;

 public:
  // ------------
  // Constructeur
  // ------------
  SooCamera();

  // ----------------------------------
  // Parametres par defaut de la camera
  // ----------------------------------
  void by_default();

  // ----------------------------
  // Reglage initial de la camera
  // ----------------------------
  void initialize();
  void focus(double size, int x, int y);
  void update();

  // ------------------------------------------------------------
  // Deplacement de la camera en fonction de la nouvelle position
  // donnee par l'utilisateur
  // ------------------------------------------------------------
  void render();

  // -------------------------------------
  // Affichage des parametres de la camera
  // -------------------------------------
  void print();

  // --------------------------------------------------
  // Modification des parametres de la camera
  // --------------------------------------------------

  void setViewport(int x, int y, int w, int h)
  { glViewport(x,y,w,h); }

  void setAlpha(float value) { alpha = value; }
  float getAlpha() { return alpha; }

  void setBeta(float value) { beta = value; }
  float getBeta() { return beta; }

  void setZoom(float value) { zoom = value; }
  float getZoom() { return zoom; }

  void setPosition(float x, float y, float z)
  { position[0] = x; position[1] = y; position[2] = z; }
  void getPosition(float &x, float &y, float &z)
  { x = position[0]; y = position[1]; z = position[2]; }

  void setTarget(float x, float y, float z)
  { target[0] = x; target[1] = y; target[2] = z; }
  void getTarget(float &x, float &y, float &z)
  { x = target[0]; y = target[1]; z = target[2]; }

  void getDirection(float * x)
    {
      x[0] = target[0] - position[0];
      x[1] = target[1] - position[1];
      x[2] = target[2] - position[2];
    }

  void setUp(float x, float y, float z)
  { up[0] = x; up[1] = y; up[2] = z; }
  void getUp(float &x, float &y, float &z)
  { x = up[0]; y = up[1]; z = up[2]; }

  void setFieldOfView(float value) { field_of_view = value; }
  float getFieldOfView() { return field_of_view; }

  void setAspectRatio(float value) { aspect_ratio = value; }
  float getAspectRatio() { return aspect_ratio; }

  void setZNear(float value) { z_near = value; }
  float getZNear() { return z_near; }

  void setZFar(float value) { z_far = value; }
  float getZFar() { return z_far; }
};

#endif /* __SOO_CAMERA_H */
