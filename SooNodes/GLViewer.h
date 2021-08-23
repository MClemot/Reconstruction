// (c) Dominique Attali 2003 (LIS)

#ifndef __GL_VIEWER_H
#define __GL_VIEWER_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/glu.h>
#include <set>

#include "SooCamera.h"
#include "SooLight.h"
#include "Quaternion.h"
#include "Vector3D.h"
#include "Mouse.h"
#include "Trackball.h"
#include "Idle.h"
#include "GLScene.h"

/**
 * @class GLViewer
 * @brief Provides functionalities to visualize and interact with a 3D scene.
 *
 * Classe permettant de visualiser et interagir avec une scene 3D.
 * La scène comporte une caméra, une lumière et un ensemble d'objets
 * dont on sait comment les afficher à l'aide d'une liste OpenGL.
 */

class GLViewer : public Fl_Gl_Window
{
protected:
  static void idle_cb(GLViewer *);
  void idle();

public:
  SooCamera * camera;
  SooLight * light[3];
  GLenum mouse_mode;		/// La souris peut etre GL_SELECT ou GL_RENDER
  GLdouble modelMatrix[16];	/// Matrice model courante
  GLdouble projMatrix[16];	/// Matrice projection courante
  GLuint depth_max;
  int depth_bits;
  int line_smooth;
  Mouse mouse;
  Trackball trackball;
  GLScene * scene;

  /** @name Constructors / Destructors / Initialization
   */
  //@{

  /**
   * Constructor.
   */
  GLViewer(int x, int y, int w, int h, const char *l = 0);

  /**
   * Destructor.
   */
  ~GLViewer();

  //@}



  /**
   * Implements the FL_Gl_Window draw method
   *
   * This method is called when the widget is to be drawn.
   */
  void draw();
  void render();

  /** Rendering */

  /** Moving and picking objects */
  // Call idle_redraw(TRUE) to force a redraw() every time idle() is
  // called.  It is initially FALSE.
  void home();
  int handle(int e);
  SooNode * select(double size, int x, int y, double * z, int * element, set<int> & set_elements);
  void resize(int X,int Y,int W,int H);
  int process(SooNode * selection, double * p, int element, set<int> & elements);

  /** Sauvegarde */
  void SaveTiff(string & file_name, int x, int y, int width, int height);

  /** Set and Get */
  void setCursor(GLenum mode);

  void changeMouseMode();
  void setMouseMode(GLenum mode);
  GLenum getMouseMode() { return mouse_mode; }
};

#endif
