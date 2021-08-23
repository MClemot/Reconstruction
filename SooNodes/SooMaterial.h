// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_MATERIAL_H
#define __SOO_MATERIAL_H

#include "SooDrawable.h"

// Implemente un material OpenGL 

class SooMaterial : public SooDrawable {
private:
  float	shininess;
  float	diffuse[4];
  float	specular[4];
  float	ambient[4];
  float	emission[4];
  float transparency;

public:
  enum {
    EMERALD, JADE, OBSEDIAN, PEARL, RUBY, TURQUOISE,
    BRASS, BRONZE, CHROME, COPPER, GOLD, SILVER,
    PLASTIC_BLACK, PLASTIC_CYAN, PLASTIC_GREEN, PLASTIC_RED, PLASTIC_WHITE, PLASTIC_YELLOW,
    RUBBER_BLACK, RUBBER_CYAN, RUBBER_GREEN, RUBBER_RED, RUBBER_WHITE, RUBBER_YELLOW,
    LIGHT_GRAY, DARK_GRAY, DARK_BLUE, DARK_BROWN
  };

  SooMaterial();
  void by_default();
  void draw();
  void print();

  void setAmbientAndDiffuse(float red, float green, float blue);

  void setShininess(float s);
  float getShininess();

  void setEmission(float red, float green, float blue);
  void getEmission(float &red, float &green, float &blue);

  void setDiffuse(float red, float green, float blue);
  void getDiffuse(float &red, float &green, float &blue);

  void setSpecular(float red, float green, float blue);
  void getSpecular(float &red, float &green, float &blue);

  void setAmbient(float red, float green, float blue);
  void getAmbient(float &red, float &green, float &blue);

  void setTransparency( GLfloat alpha );
  GLfloat getTransparency();

  void set(GLfloat ambr, GLfloat ambg, GLfloat ambb,
	   GLfloat difr, GLfloat difg, GLfloat difb,
	   GLfloat specr, GLfloat specg, GLfloat specb,
	   GLfloat shine);

  void set(int);
};

#endif

