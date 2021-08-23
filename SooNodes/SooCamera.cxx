// (c) Dominique Attali 2003 (LIS)

#include <stdio.h>
#include<iostream>
#include "SooCamera.h"

// ================================================
//
// C O N S T R U C T E U R   D E   L A   C L A S S E   C A M E R A
//
// ================================================

SooCamera::SooCamera() : SooNode("Camera")
{
  by_default();
  initialized = 0;
}

// ================================================
//
// P A R A M E T R E S   P A R   D E F A U T   D E   L A   C A M E R A
//
// ================================================

void
SooCamera::by_default()
{
  // Position initiale de la camera
  // ----------------------------------------------
  setPosition(9.0, 0.0, 0.0);

  // Vers ou la camera pointe
  // Initialement, la camera pointe vers l'origine (0.0, 0.0, 0.0)
  // ----------------------------------------------
  setTarget(0.0, 0.0, 0.0);
  
  // Vecteur de projection verticale
  // Initialement, la camera est posee verticalement
  // selon la direction (Oz)
  // ----------------------------------------------
  setUp(0.0, 0.0, 1.0);
  
  // Angle d'ouverture de la camera
  setFieldOfView(40.0);
 
  // Deformation entre l'horizontale et la verticale
  // Initialement, la camera a un aspect ration de 1
  // ----------------------------------------------
  setAspectRatio(1.0);

  // Position des plans de coupures de la camera
  // La camera voit uniquement les objets places
  // entre z_far et z_near
  // Initialement, les plans de coupures sont
  // places de facon a etre sur de voir la totalite
  // des objets
  // ----------------------------------------------
  setZNear(1.0);
  setZFar(17.0);

  // Rotations et zoom initiales de la camera
  // ----------------------------------------------
  setAlpha(-70.0);
  setBeta(28.0);
  setZoom(2.0);
}

// ================================================
//
// R E G L A G E   I N I T I A L   D E   L A   C A M E R A
//
// ================================================

void
SooCamera::update()
{
  if (initialized) return;

  // Set camera perspective
  // ----------------------
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();	 
  gluPerspective(field_of_view, aspect_ratio, z_near, z_far);
  
  // Set camera position and target
  // ------------------------------
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(position[0], position[1], position[2],
	    target[0], target[1], target[2],
	    up[0], up[1], up[2]
	    );

  // move stuff into center of view volume
  glTranslatef(target[0], target[1], target[2]);
}

void
SooCamera::focus(double size, int x, int y)
{
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();	 
  gluPickMatrix((GLdouble) x, (GLdouble) y, size, size, viewport);
  gluPerspective(field_of_view, aspect_ratio, z_near, z_far);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(position[0], position[1], position[2],
	    target[0], target[1], target[2],
	    up[0], up[1], up[2]
	    );

  glTranslatef(target[0], target[1], target[2]);
  
}

void
SooCamera::initialize()
{
  if (!initialized)
    {
      update();
      initialized = 1;
    }
}

// ================================================
//
// D E P L A C E M E N T   D E   L A   C A M E R A   E N   F O N C T I O N
//
// D E   L A   N O U V E L L E   P O S I T I O N   D O N N E E
//
// P A R   L ' U T I L I S A T E U R
//
// ================================================

void
SooCamera::render()
{
  if (!getDisplay()) return;

  glScalef(zoom, zoom, zoom);
  glRotatef(beta, 0.0, 1.0, 0.0);
  glRotatef(alpha, 0.0, 0.0, 1.0);
}

// ================================================
//
// A F F I C H A G E   D E S   P A R A M E T R E S   D E   L A   C A M E R A
//
// ================================================

void
SooCamera::print()
{
  printf("Camera : \n");
  printf("  - position =\t(%lf,%lf,%lf)\n", position[0], position[1], position[2]);
  printf("  - target =\t(%lf,%lf,%lf)\n", target[0], target[1], target[2]);
  printf("  - up =\t(%lf,%lf,%lf)\n", up[0], up[1], up[2]);
  printf("  - field_of_view =\t%lf\n", field_of_view);
  printf("  - aspect_ratio =\t%lf\n", aspect_ratio);
  printf("  - z_near =\t%lf\n", z_near);
  printf("  - z_far =\t%lf\n", z_far);
  printf("  - alpha =\t%lf\n", alpha);
  printf("  - beta =\t%lf\n", beta);
  printf("  - zoom =\t%lf\n", zoom);

  GLdouble m[16];
  glGetDoublev(GL_MODELVIEW_MATRIX, m);

  printf("\nMODELVIEW =  %.2lf %.2lf %.2lf %.2lf\n", m[0], m[4], m[8], m[12]);
  printf("             %.2lf %.2lf %.2lf %.2lf\n", m[1], m[5], m[9], m[13]);
  printf("             %.2lf %.2lf %.2lf %.2lf\n", m[2], m[6], m[10], m[14]);
  printf("             %.2lf %.2lf %.2lf %.2lf\n", m[3], m[7], m[11], m[15]);

  glGetDoublev(GL_PROJECTION_MATRIX, m);

  printf("\nPROJECTION = %.2lf %.2lf %.2lf %.2lf\n", m[0], m[4], m[8], m[12]);
  printf("             %.2lf %.2lf %.2lf %.2lf\n", m[1], m[5], m[9], m[13]);
  printf("             %.2lf %.2lf %.2lf %.2lf\n", m[2], m[6], m[10], m[14]);
  printf("             %.2lf %.2lf %.2lf %.2lf\n", m[3], m[7], m[11], m[15]);
 

}


