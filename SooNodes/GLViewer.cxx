// (c) Dominique Attali 2003 (LIS)

#include <stdio.h>
#include <FL/fl_draw.H>
#include <set>
#include "Idle.h"
#include "Misc.h"
#include "GLViewer.h"

// ================================================
//
//   I N I T I A L I Z A T I O N
//
// ================================================

GLViewer::GLViewer
(int x, int y, int w, int h, const char *l)
  : Fl_Gl_Window(x, y, w, h, l), trackball(mouse)
{
  mode( FL_RGB | FL_DEPTH | FL_DOUBLE);

  line_smooth = 1;

  // ----- CAMERA INITIALIZATION
  camera = new SooCamera();
  camera->setPosition(0.0, 0.0, 0.0);
  camera->setTarget(0.0, 0.0, -5.0);
  camera->setUp(0.0, 1.0, 0.0);
  camera->setFieldOfView(40.0);
  camera->setAspectRatio(1.0);
  camera->setZNear(1.0);
  camera->setZFar(9.0);

  // ----- LIGHTS INITIALIZATION
  for (int i=0;i<3;i++)
    light[i] = new SooLight();

  light[0]->setAlpha(127.0);
  light[0]->setBeta(31.0);
  //  light[1]->isOn(0);

  for (int i=0;i<3;i++)
    {
      light[i]->printTree();
      cout << "Alpha(Light " << i << ") = " << light[i]->getAlpha() << endl;
      cout << "Beta(Light " << i << ") = " << light[i]->getBeta() << endl;
    }

  // ----- MOUSE MODE INITIALIZATON
  mouse_mode = GL_RENDER;

  // -----  INITIALIZATION
  home();
}

void GLViewer::home()
{
  SetNoIdle();
  trackball.Reset();
  mouse.SetWindowSize(w(), h());  
}

GLViewer::~GLViewer()
{
  delete light[0];
  delete light[1];
  delete light[2];

#ifdef DEBUG
  cout << "GLViewer destroyed" << endl;
#endif
}

// ================================================
//
//   R E S H A P E
//
// ================================================

// Que faire lorsque la fenetre change de taille
void
GLViewer::resize(int X,int Y,int W,int H)
{
  if (W != w() || H != h())
    {
      glViewport(X, Y, W, H);
      mouse.SetWindowSize(W, H);
    }
  Fl_Gl_Window::resize(X,Y,W,H);
}

// ================================================
//
//   R E N D E R I N G
//
// ================================================

void
GLViewer::draw()
{
  GLint viewport[4];

  if (!valid())
    {
      float modelAmb[4] = {0.2, 0.2, 0.2, 1.0};
      float bias = 0.5;
      float factor = 1.0;

      glViewport(0, 0, w(), h());
      camera->initialize();
      camera->print();

      // ---------------
      // Set light model
      // ---------------
      glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmb);
      glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
      glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

      glEnable(GL_AUTO_NORMAL);
      glEnable(GL_NORMALIZE);
      glEnable(GL_DEPTH_TEST);

      glPolygonOffset(factor, bias);
#ifdef GL_EXT_polygon_offset
      glEnable(GL_POLYGON_OFFSET_EXT);
#endif

      glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

      glDepthMask(GL_TRUE);
      glEnable(GL_BLEND);
      #ifndef _WIN32
      glBlendEquation(GL_FUNC_ADD);
      #endif
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      // Sur les conseils de :
      // http://www.openglsuperbible.com/2013/08/20/is-order-independent-transparency-really-necessary/
      //glBlendFunc(GL_ZERO, GL_SRC_COLOR);


      if (line_smooth)
	glEnable(GL_LINE_SMOOTH);

      glGetIntegerv(GL_DEPTH_BITS, &depth_bits);
      depth_max = 0xffffffff;
      printf("depth_max : %x\n", depth_max);
    }

  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  light[0]->render();
  light[1]->render();
  light[2]->render();
  trackball.DoTransform();
  scene->DoTransform();

  if (mouse_mode == GL_RENDER)
    {
      glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
      glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

      // Below are the magic lines for computing the camera position
      glGetIntegerv(GL_VIEWPORT, viewport);
      gluUnProject((viewport[2]-viewport[0])/2, (viewport[3]-viewport[1])/2, 0.0
		   , modelMatrix, projMatrix, viewport
		   , &scene->camera_position[0], &scene->camera_position[1], &scene->camera_position[2]);
    }

  render();
  glPopMatrix();
}

void 
GLViewer::render()
{
  scene->render(); 
}

// ================================================
//
//   S E L E C T I N G   O B J E C T S
//
// ================================================

SooNode *
GLViewer::select(double size, int x, int y, double * z, int * element, set<int> & set_elements)
{
  const int BUFSIZE = 512;
  GLuint selectBuf[BUFSIZE];
  GLint hits;
  GLuint names, *ptr, profondeur;
  SooNode * node = NULL;
  int i;

  glSelectBuffer(BUFSIZE, selectBuf);
  (void) glRenderMode(GL_SELECT);
  glEnable(GL_DEPTH_TEST);

  glInitNames();
  glPushName(0);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  camera->focus(size, x, y);
  draw();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  hits = glRenderMode(GL_RENDER);

  // ------ TRAITEMENT DU HIT
  printHits(hits,selectBuf);

  if (hits==0) return NULL;

  ptr = (GLuint * )selectBuf;
  profondeur = depth_max;
  for (i=0;i<hits;i++)
    {
      names = *ptr;
      if (profondeur>ptr[1])
	{
	  profondeur = ptr[1];
	  node = findPtrSooNode(ptr[3]);
	  *z = (double)profondeur/(double)(depth_max);
	  if (names>1) (*element) = ptr[4];
	}
      ptr+=names+3;
    }

  insertElements(hits,selectBuf,node,set_elements);

  return node;
}

int
GLViewer::process(SooNode * selection, double * point, int element, set<int> & set_elements)
{
  if (selection)
    {
      cout << "Selection : " << selection->getName() << " ";
      cout << "(" << point[0] << " " << point[1] << " " << point[2] << ") " << element << endl;
      
      cout << "Elements in selection :";
      set<int>::iterator it;
      for (it = set_elements.begin(); it != set_elements.end(); it++)
	cout << " " << *it;
      cout << endl;

      if (scene->process(selection, point, element, set_elements))
	redraw();
    }

  return 1;
}

// ================================================
//
//   S A V E
//
// ================================================

void
GLViewer::SaveTiff(string & file_name, int x, int y, int width, int height)
{
  glViewport(0, 0, width, height);
  draw();
  const char * description = "3D SCENE";
  writetiff(file_name, description, x, y, width, height, COMPRESSION_NONE);
  glViewport(0, 0, w(), h());
  redraw();
}


// ================================================
//
//   S E T
//
// ================================================

void
GLViewer::setCursor(GLenum mode)
{
  switch (mode)
    {
    case GL_SELECT:
      fl_cursor(FL_CURSOR_HAND,FL_BLACK,FL_WHITE);
      break;
    case GL_RENDER:
      fl_cursor(FL_CURSOR_DEFAULT,FL_BLACK,FL_WHITE);
      break;
    }
}

void
GLViewer::changeMouseMode()
{
  mouse_mode = (mouse_mode==GL_RENDER)?GL_SELECT:GL_RENDER;
  setCursor(mouse_mode);
  if (mouse_mode == GL_SELECT)
    SetNoIdle();
  else
    SetIdle();
}

void
GLViewer::setMouseMode(GLenum mode)
{
  if (mouse_mode != mode) changeMouseMode();
}

// ================================================
//
//   M O V I N G   O B J E C T S
//
// ================================================

// The handle() method just records the events, and the idle callback
// does the actual work.

int GLViewer::handle(int e)
{
  if (Fl::event_state(FL_SHIFT))
    {
      setMouseMode(GL_SELECT);

      switch(e) {
      case FL_PUSH:
	double point[3];
	double depth;
	int element = -1;
	set<int> set_elements;
	SooNode * selection;
	GLint viewport[4];
	GLint real_y;
	
	glGetIntegerv(GL_VIEWPORT, viewport);
	real_y = viewport[3] - (GLint) Fl::event_y() - 1;
	selection = select(5.0, Fl::event_x(), real_y, &depth, &element, set_elements);
	gluUnProject((double) Fl::event_x(), (double) real_y, depth
		     , modelMatrix, projMatrix, viewport
		     , point, point+1, point+2);
	return process(selection, point, element, set_elements);
      }
    }
  else
    {
      setMouseMode(GL_RENDER);

      switch (e) {
      case FL_PUSH:
	mouse.UpdatePos(Fl::event_x(),Fl::event_y());
	mouse.UpdatePos(Fl::event_x(),Fl::event_y());
	mouse.UpdateButtons(Fl::event_state() & BUTTON_MASK);
	SetNoIdle();
	// --------
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);   
	// --------
	idle();
	return 1;
      case FL_RELEASE:
	mouse.UpdateButtons(Fl::event_state() & BUTTON_MASK);
	if (trackball.isSpinning)
	  SetIdle((void (*)(void *))idle_cb, this);
	else
	  {
	    // --------
	    glEnable(GL_BLEND);
	    if (line_smooth)
	      glEnable(GL_LINE_SMOOTH);	// A mettre en commentaire s'il faut
	    scene->UpdateWithCamera();
	    redraw();
	    // --------
	  }
	return 1;
      case FL_DRAG:
	mouse.UpdatePos(Fl::event_x(),Fl::event_y());
	mouse.UpdateButtons(Fl::event_state() & BUTTON_MASK);
	idle();
	return 1;
      case FL_MOUSEWHEEL:
	if (Fl::event_dy() != 0)
	  {
	    scene->zoom(Fl::event_dy());
	    redraw();
	  }
	return 1;
      }
    }
  return 0;
}

void GLViewer::idle_cb(GLViewer *t) {
  t->idle();
}

void GLViewer::idle() {
  trackball.Update();
  if (trackball.isSpinning || trackball.isChanged) {
    redraw();
    trackball.isChanged = false;
  }
}

