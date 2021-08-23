// (c) Dominique Attali 2003 (LIS)

#include <stdio.h>
#include "SooMaterial.h"

// ------------------------------------------------------------
void
SooMaterial::by_default()
{
  setAmbient(0.2, 0.2, 0.2);
  setDiffuse(0.8, 0.8, 0.8);
  setSpecular(0.0, 0.0, 0.0);
  setShininess(0.0);
  setEmission(0.0, 0.0, 0.0);
  setTransparency(0.0);
}
 
// ------------------------------------------------------------
SooMaterial::SooMaterial() : SooDrawable("Material")
{
  by_default();
}

// ------------------------------------------------------------
void
SooMaterial::draw()
{
  glEnable(GL_LIGHTING);

#if 0
  if( (transparency>0.) && (transparency<=1.) )
    {
      glDepthMask (GL_FALSE);
      glEnable(GL_BLEND);
    }
  else
    {
      glDisable(GL_BLEND);
      glDepthMask (GL_TRUE);
    }
#endif

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);	
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

// ------------------------------------------------------------
void
SooMaterial::setDiffuse(float red, float green, float blue)
{
  diffuse[0] = red;
  diffuse[1] = green;
  diffuse[2] = blue;
  touch();
}

// ------------------------------------------------------------
void
SooMaterial::setSpecular(float red, float green, float blue)
{
  specular[0] = red;
  specular[1] = green;
  specular[2] = blue;
  touch();
}

// ------------------------------------------------------------
void
SooMaterial::setAmbient(float red, float green, float blue)
{
  ambient[0] = red;
  ambient[1] = green;
  ambient[2] = blue;
  touch();
}

// ------------------------------------------------------------
void
SooMaterial::setAmbientAndDiffuse(float red, float green, float blue)
{
  diffuse[0] = ambient[0] = red;
  diffuse[1] = ambient[1] = green;
  diffuse[2] = ambient[2] = blue;
  touch();
}

// ------------------------------------------------------------
void
SooMaterial::getDiffuse(float &red, float &green, float &blue)
{
  red = diffuse[0];
  green = diffuse[1];
  blue = diffuse[2];
}

// ------------------------------------------------------------
void
SooMaterial::getSpecular(float &red, float &green, float &blue)
{
  red = specular[0];
  green = specular[1];
  blue = specular[2];
}

// ------------------------------------------------------------
void
SooMaterial::getAmbient(float &red, float &green, float &blue)
{
  red = ambient[0];
  green = ambient[1];
  blue = ambient[2];
}

// ------------------------------------------------------------
void
SooMaterial::setEmission(float red, float green, float blue)
{
  emission[0] = red;
  emission[1] = green;
  emission[2] = blue;
  touch();
}

// ------------------------------------------------------------
void
SooMaterial::getEmission(float &red, float &green, float &blue)
{
  red = emission[0];
  green = emission[1];
  blue = emission[2];
}

// ------------------------------------------------------------
void
SooMaterial::setShininess(float s)
{
  shininess = s;
  touch();
}

// ------------------------------------------------------------
float
SooMaterial::getShininess()
{
  return shininess;
}

// ------------------------------------------------------------
void
SooMaterial::set(GLfloat ambr, GLfloat ambg, GLfloat ambb,
	 GLfloat difr, GLfloat difg, GLfloat difb,
	 GLfloat specr, GLfloat specg, GLfloat specb,
	 GLfloat shine)
{
  setAmbient( ambr, ambg, ambb );
  setDiffuse( difr, difg, difb );
  setSpecular( specr, specg, specb );
  setEmission( 0.0, 0.0, 0.0 );
  setShininess( shine * 128.0 );
}


// ------------------------------------------------------------
void
SooMaterial::set(int MATERIAL)
{
  switch (MATERIAL)
    {
    case EMERALD:
      set(0.0215, 0.1745, 0.0215, 0.07568, 0.61424, 0.07568, 0.633, 0.727811, 0.633, 0.6);
      break;
    case JADE:
      set(0.135, 0.2225, 0.1575, 0.54, 0.89, 0.63, 0.316228, 0.316228, 0.316228, 0.1);
      break;
    case OBSEDIAN:
      set(0.05375, 0.05, 0.06625, 0.18275, 0.17, 0.22525, 0.332741, 0.328634, 0.346435, 0.3);
      break;
    case PEARL:
      set(0.25, 0.20725, 0.20725, 1, 0.829, 0.829, 0.296648, 0.296648, 0.296648, 0.088);
      break;
    case LIGHT_GRAY:
      set(0.25, 0.20725, 0.20725, 0.8, 0.829, 0.829, 0.296648, 0.296648, 0.296648, 0.088);
      break;
    case RUBY:
      set(0.1745, 0.01175, 0.01175, 0.61424, 0.04136, 0.04136, 0.727811, 0.626959, 0.626959, 0.6);
      break;
    case TURQUOISE:
      set(0.1, 0.18725, 0.1745,0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1);
      break;
    case BRASS:
      set(0.329412, 0.223529, 0.027451,
	  0.780392, 0.568627, 0.113725, 0.992157, 0.941176, 0.807843, 0.21794872);
      break;
    case BRONZE:
      set(0.2125, 0.1275, 0.054,
	  0.714, 0.4284, 0.18144, 0.393548, 0.271906, 0.166721, 0.2);
      break;
    case CHROME:
      set(0.25, 0.25, 0.25,
	  0.4, 0.4, 0.4, 0.774597, 0.774597, 0.774597, 0.6);
      break;
    case COPPER:
      set(0.19125, 0.0735, 0.0225,
	  0.7038, 0.27048, 0.0828, 0.256777, 0.137622, 0.086014, 0.1);
     break;
    case GOLD:
      set(0.24725, 0.1995, 0.0745,
	  0.75164, 0.60648, 0.22648, 0.628281, 0.555802, 0.366065, 0.4);
     break;
    case SILVER:
      set(0.19225, 0.19225, 0.19225,
	  0.50754, 0.50754, 0.50754, 0.508273, 0.508273, 0.508273, 0.4);
      break;
    case PLASTIC_BLACK:
      set(0.0, 0.0, 0.0, 0.01, 0.01, 0.01,
	  0.50, 0.50, 0.50, .25);
      break;
    case DARK_GRAY:
      set(0.01, 0.01, 0.01, 0.1, 0.1, 0.1,
	  0.40, 0.40, 0.40, .078125);
      break;
    case DARK_BROWN:
      set(0.01, 0.01, 0.01, 99.0/255.0, 6.0/255.0, 17.0/255.0,
	  0.40, 0.40, 0.40, .078125);
      break;
    case DARK_BLUE:
      set(0.01, 0.01, 0.01, 0.153, 0.2, 0.565,
	  0.40, 0.40, 0.40, .078125);
      break;
    case PLASTIC_CYAN:
      set(0.0, 0.1, 0.06, 0.0, 0.50980392, 0.50980392,
	  0.50196078, 0.50196078, 0.50196078, .25);
      break;
    case PLASTIC_GREEN:
      set(0.0, 0.0, 0.0,
	  0.1, 0.35, 0.1, 0.45, 0.55, 0.45, .25);
      break;
    case PLASTIC_RED:
      set(0.0, 0.0, 0.0, 0.5, 0.0, 0.0,
	  0.7, 0.6, 0.6, .25);
      break;
    case PLASTIC_WHITE:
      set(0.0, 0.0, 0.0, 0.55, 0.55, 0.55,
	  0.70, 0.70, 0.70, .25);
      break;
    case PLASTIC_YELLOW:
      set(0.0, 0.0, 0.0, 0.5, 0.5, 0.0,
	  0.60, 0.60, 0.50, .25);
      break;
    case RUBBER_BLACK:
      set(0.02, 0.02, 0.02, 0.01, 0.01, 0.01,
	  0.4, 0.4, 0.4, .078125);
      break;
    case RUBBER_CYAN:
      set(0.0, 0.05, 0.05, 0.4, 0.5, 0.5,
	  0.04, 0.7, 0.7, .078125);
      break;
    case RUBBER_GREEN:
      set(0.0, 0.05, 0.0, 0.4, 0.5, 0.4,
	  0.04, 0.7, 0.04, .078125);
      break;
    case RUBBER_RED:
      set(0.05, 0.0, 0.0, 0.5, 0.4, 0.4,
	  0.7, 0.04, 0.04, .078125);
      break;
    case RUBBER_WHITE:
      set(0.05, 0.05, 0.05, 0.5, 0.5, 0.5,
	  0.7, 0.7, 0.7, .078125);
      break;
    case RUBBER_YELLOW:
      set(0.05, 0.05, 0.0, 0.5, 0.5, 0.4,
	  0.7, 0.7, 0.04, .078125);
      break;
    }
}

// ------------------------------------------------------------
void
SooMaterial::print()
{
  printf("Material :\n");
  printf("  - diffuse =\t(%lf,%lf,%lf,%lf)\n", diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
  printf("  - ambient =\t(%lf,%lf,%lf,%lf)\n", ambient[0], ambient[1], ambient[2], ambient[3]);
  printf("  - emission =\t(%lf,%lf,%lf,%lf)\n", emission[0], emission[1], emission[2], emission[3]);
  printf("  - specular =\t(%lf,%lf,%lf,%lf)\n", specular[0], specular[1], specular[2], specular[3]);
  printf("  - shininess = %lf\n", shininess);
}

void
SooMaterial::setTransparency( GLfloat t )
{
  transparency = t;
  ambient[3] = 1.0 - transparency;
  diffuse[3] = 1.0 - transparency;
  specular[3] = 1.0 - transparency;
  emission[3] = 1.0 - transparency;
  touch();
}

GLfloat
SooMaterial::getTransparency( )
{
  return transparency;
}

