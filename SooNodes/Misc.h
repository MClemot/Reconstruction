// (c) Dominique Attali 2003 (LIS)

// ================================================
//
// FONCTIONS DE BASE
//
// ================================================

#ifndef __MISC_H
#define __MISC_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <iomanip>
#include <locale>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <tiffio.h>     /* Sam Leffler's libtiff library. */
#include <FL/gl.h>
#include <FL/glu.h>
#include "SooNode.h"

// Defining own numeric facet:

class WithComma: public numpunct<char> // class for decimal numbers using comma instead of point
{
    protected:
        char do_decimal_point() const { return ','; } // change the decimal separator
};

/*
 * Display the time left in a computation.
 *
 */
class Timer
{
  int cpt_max;  // Number of dots to show the time left
  int cpt;
  int k_max;
  int k;

 public:
  Timer(int c = 20)
    {
      cpt_max = c;
      if (cpt_max < 1) cpt_max = 1;
    }

  void Begin(int n)
  {
    k_max = n;
    k = 1;
    cpt = 1;		/* Permet de visualiser le temp restant */

    for (int i=0;i<cpt_max;i++) { printf(".");fflush(stdout); }
    for (int i=0;i<cpt_max;i++) printf("\010");
  }

  void Inc()
  {
    if ((int)(cpt_max*(double)k/(double)k_max)==cpt)
      { printf("o");fflush(stdout);cpt++; }
    k++;
  }

  void End()
  {
    while (cpt<=cpt_max)
      { printf("o");fflush(stdout);cpt++; }
  }
};



// Renvoie la date
extern void
pcp_gettime(double *t);

// Sauvegarde une image au format tiff
extern int
writetiff(string & filename, const char *description, int x, int y, int width, int height, int compression);

extern void
printHits(GLint hits, GLuint buffer[]);

extern void
insertElements(GLint hits, GLuint * selectBuf, SooNode * node, set<int> & set_elements);

extern void
BeginTexture(int width, int height, GLubyte * image);

extern void
EndTexture();


extern float green(float x);
extern float red(float x);
extern float blue(float x);
extern float gray(float x);

extern string getShortName(const char * file_name);
extern char * getFullName(string & name);
extern string ConvertNumber(double number, int precision);

#endif
