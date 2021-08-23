// (c) Dominique Attali 2003 (LIS)

#ifdef _WIN32
#include <windows.h>
#include <stdint.h>
int gettimeofday(struct timeval* tp, struct timezone* tzp)
{
    static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime(&system_time);
    SystemTimeToFileTime(&system_time, &file_time);
    time = ((uint64_t)file_time.dwLowDateTime);
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec = (long)((time - EPOCH) / 10000000L);
    tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
    return 0;
}
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <math.h>
#include <GL/gl.h>
#ifndef _WIN32
#include <GL/glext.h>
#endif
#include <FL/fl_draw.H>
#include <boost/algorithm/string.hpp>
#include <vector>
#include "Misc.h"

using namespace boost;
using namespace std;

void pcp_gettime(double *t)
{
  struct timeval tp;
  if (gettimeofday(&tp,(struct timezone *) NULL) == 0)
    *t = (double) tp.tv_sec + (double) tp.tv_usec / (double) 1E6;
  else *t=0;
}

// ================================================
//
//    R E A D I N G   A N D   W R I T I N G
//
// ================================================

string getShortName(const char * name)
{
  string s(name);
  vector <string> fields;
  vector <string> path;

  cout << "string : [" << name << "]" << endl;
  split( fields, s, is_any_of( "." ) );
  split( path, fields[0], is_any_of("/") );

  cout << "Short name : [" << path.back() << "]" << endl;

  return path.back();
}

char * getFullName(string & name)
{
  string fullname = "../Data/3d/" + name + ".obj";
  char * filename = new char[fullname.length() + 1];
  std::strcpy(filename, fullname.c_str());
  return filename;
}

string ConvertNumber(double number, int precision)
{
  ostringstream Convert;
  locale MyLocale(  locale(), new WithComma); // Create customized locale
  Convert.imbue(MyLocale);       // Imbue the custom locale to the stringstream
  Convert << fixed << setprecision(precision) << number; // Use some manipulators
  string result = Convert.str(); // Give the result to the string
  return result;
}


int
writetiff(string & name, const char *description,
  int x, int y, int width, int height, int compression)
{
  char *filename = new char[name.length() + 1];
  TIFF *file;
  GLubyte *image, *p;
  int i;

  std::strcpy(filename, name.c_str());
  file = TIFFOpen(filename, "w");
  if (file == NULL) {
    return 1;
  }
  image = (GLubyte *) malloc(width * height * sizeof(GLubyte) * 3);

  /* OpenGL's default 4 byte pack alignment would leave extra bytes at the
     end of each image row so that each full row contained a number of bytes
     divisible by 4.  Ie, an RGB row with 3 pixels and 8-bit componets would
     be laid out like "RGBRGBRGBxxx" where the last three "xxx" bytes exist
     just to pad the row out to 12 bytes (12 is divisible by 4). To make sure
     the rows are packed as tight as possible (no row padding), set the pack
     alignment to 1. */
  glPixelStorei(GL_PACK_ALIGNMENT, 1);

  glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
  TIFFSetField(file, TIFFTAG_IMAGEWIDTH, (uint32) width);
  TIFFSetField(file, TIFFTAG_IMAGELENGTH, (uint32) height);
  TIFFSetField(file, TIFFTAG_BITSPERSAMPLE, 8);
  TIFFSetField(file, TIFFTAG_COMPRESSION, compression);
  TIFFSetField(file, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
  TIFFSetField(file, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
  TIFFSetField(file, TIFFTAG_SAMPLESPERPIXEL, 3);
  TIFFSetField(file, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
  TIFFSetField(file, TIFFTAG_ROWSPERSTRIP, 1);
  TIFFSetField(file, TIFFTAG_IMAGEDESCRIPTION, description);
  p = image;
  //  for (i = height - 1; i >= 0; i--) {
  for (i = 0; i < height; i++) {
    if (TIFFWriteScanline(file, p, height - i - 1, 0) < 0) {
      free(image);
      TIFFClose(file);
      return 1;
    }
    p += width * sizeof(GLubyte) * 3;
  }
  TIFFClose(file);

  delete[] filename;
  return 0;
}

// ================================================
//
//    D O   S E L E C T
//
// ================================================

// Affiche le resultat d'une operation de Picking
void
printHits(GLint hits, GLuint buffer[])
{
  GLuint names, *ptr;
  SooNode * node;
  int i, j;
  ptr = (GLuint * )buffer;
  printf("\n\nSELECTION : %d objects\n",hits);

  for (i=0;i<hits;i++)
    {
      names = *ptr;ptr+=3;
      node = findPtrSooNode(*ptr); ptr++;
      cout << "node = " << node->getName(); fflush(stdout);

      for (j=1;j<names;j++)
        {
          if (j==1) { printf(" (Part : "); fflush(stdout); }
          printf(" %d", *ptr ); fflush(stdout);
          if (j==names-1) printf(")");
          ptr++;
        }

      printf("\n");
    }
}


// Affiche le resultat d'une operation de Picking
void
insertElements(GLint hits, GLuint * selectBuf, SooNode * node, set<int> & set_elements)
{
  GLuint * ptr = selectBuf;
  GLuint names;

  for (int i=0; i<hits; i++)
    {
      names = *ptr;ptr+=3;
      if (node == findPtrSooNode(*ptr))
        {
          ptr++;
          for (int j=1; j<names; j++)
            {
              set_elements.insert(*ptr);
              ptr++;
            }
        }
      else
        ptr+=names;
    }
}

// ================================================
//
//    T E X T U R E
//
// ================================================

// Prepare la texture
void
BeginTexture(int width, int height, GLubyte * image)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  glEnable(GL_TEXTURE_2D);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glShadeModel(GL_FLAT);
}

void
EndTexture()
{
  glDisable(GL_TEXTURE_2D);
}

// ================================================
//
//    C O L O R
//
// ================================================

float gray(float x)
{
  if (x>1.0)
    return 0.0;
  else if (x<0.0)
    return 0.8;
  return -0.8*x+0.8;

}

float red(float x)
{
  if (x>1.0)
    return 1.0;
  else if (x<0.0)
    return 0.5;
  else if (x<0.2)
    return (-5.0*x+1)/2.0;
  else if (x>0.6)
    return (5.0*x-3.0)/2.0;
  return 0.0;
}

float blue(float x)
{
  if (x<0.2)
    return (5.0*x+1.0)/2.0;
  else if (x<0.6)
    return (-5.0*x+3.0)/2.0;
  return 0.0;
}

float green(float x)
{
  if (x>1.0)
    return 0.0;
  else if (x>0.6)
    return (-5.0*x+5.0)/2.0;
  else if (x>0.2)
    return (5.0*x-1.0)/2.0;
  return 0.0;
}
