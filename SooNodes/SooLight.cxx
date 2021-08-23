// (c) Dominique Attali 2003 (LIS)

#include <stdio.h>
#include <math.h>
#include "SooLight.h"

long SooLight::lightmask = 0;

// ================================================
//
// C O N S T R U C T E U R   D E   L A   S O U R C E   L U M I N E U S E
//
// ================================================

SooLight::SooLight() : SooNode("Light")
{
  // La source de lumiere se voit attribuer
  // un numero unique entre 0 et 7 de facon
  // automatique au moment de sa construction
  // Si toutes les lumieres sont deja utilisees,
  // le numero numero vaudra -1
  number = -1;
	
  for ( int i = 0 ; i < MAX_LIGHTS ; ++i ) {
    if ( !(lightmask & 1 << i) ) {
      //bit i is empty i.e. light i is available
      number = i;
      lightmask = lightmask | 1 << i;
      break;
    }
  }

  by_default();
}

// ================================================
//
// P A R A M E T R E S   P A R   D E F A U T   D E   L A   S O U R C E   L U M I N E U S E
//
// ================================================

void
SooLight::by_default()
{
  setAmbient(0.0, 0.0, 0.0, 1.0 );
  
  if ( number == 0 )
    {
      //      setPosition(0.276781,-0.111827,2.431233,0.000000);
      //      setPosition(2.168140,-1.057473,-0.425350,0.000000);
      setPosition(3, 0, 0, 0);
      setDiffuse(1.0, 1.0, 1.0, 1.0);
      setSpecular(1.0, 1.0, 1.0, 1.0);
      isOn(1);
    }
  else if ( number == 1 )
    {
      //      setPosition(-1.033781,2.216949,-0.128196,0.000000);
      setPosition(-0.993464,1.418813,1.732051,0.000000);
      setDiffuse(0.4, 0.4, 0.4, 1.0);
      setSpecular(0.5, 0.5, 0.5, 1.0);
      isOn(1);
    }
  else
    {
      setPosition(-0.356728,0.231662,2.412276,0.000000);
      setDiffuse(0.0, 0.0, 0.0, 1.0);
      setSpecular(0.0, 0.0, 0.0, 1.0);
      isOn(0);
    }

  setConstantAttenuation( 1 );
  setLinearAttenuation( 0 );
  setQuadraticAttenuation( 0 );
  setSpotCutoff(180.0);
  setSpotDirection(-1.0,0.0,0.0);
  setSpotExponent(0.0);
}

// ================================================
//
// D E S T R U C T E U R   D E   L A   S O U R C E   L U M I N E U S E
//
// ================================================

SooLight::~SooLight()
{
  if ( number != -1 ) 
    lightmask = lightmask ^ (1 << number); 
}

// ================================================
//
// R E N D U   O P E N G L   D E   L A   S O U R C E   L U M I N E U S E
//
// ================================================

void
SooLight::drawArrow(GLfloat * position, GLfloat * color)
{
  GLfloat alpha = atan2(position[1],position[0]) * 180 / M_PI; 
  GLfloat beta = atan2(hypot(position[0],position[1]),position[2]) * 180.0 / M_PI;
  GLfloat size = 0.05;

  glPushMatrix();
  glDisable(GL_LIGHTING);
  glColor3fv(color);

  glTranslatef(position[0],position[1],position[2]);
  glRotatef(alpha, 0.0, 0.0, 1.0);
  glRotatef(beta, 0.0, 1.0, 0.0);

  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0,-size,2*size);
  glVertex3f(0.0,size,2*size);
  glVertex3f(0.0,size,0.0);
  glVertex3f(0.0,2*size,0.0);
  glVertex3f(0.0,0.0,-2*size);
  glVertex3f(0.0,-2*size,0.0);
  glVertex3f(0.0,-size,0.0);
  glEnd();
  glPopMatrix();
}

void
SooLight::render()
{
  if ( number == -1 ) return;
  GLenum light = (GLenum)(GL_LIGHT0 + number);

  if (on)
    {
      glEnable( light );
      
      glLightfv( light, GL_AMBIENT, ambient );
      glLightfv( light, GL_DIFFUSE, diffuse );
      glLightfv( light, GL_SPECULAR, specular );
      glLightfv( light, GL_POSITION, position );
      glLightf( light, GL_CONSTANT_ATTENUATION, constatt );
      glLightf( light, GL_LINEAR_ATTENUATION, linatt );
      glLightf( light, GL_QUADRATIC_ATTENUATION, quadatt );

      glLightf( light, GL_SPOT_CUTOFF, spot_cutoff);
      glLightfv( light, GL_SPOT_DIRECTION, spot_direction);
      glLightf( light, GL_SPOT_EXPONENT, spot_exponent);

      // drawArrow(position,diffuse);
    }
  else
    glDisable( light );
}

// ================================================
//
// A F F I C H A G E   D E S   P A R A M E T R E S   D E   L A   S O U R C E   L U M I N E U S E
//
// ================================================

void SooLight::print()
{
  printf("Light %d : ", number); fflush(stdout);
  if (on) printf("on\n"); else printf("off\n");
  printf("  - diffuse =\t(%lf,%lf,%lf)\n", diffuse[0], diffuse[1], diffuse[2]);
  printf("  - ambient =\t(%lf,%lf,%lf)\n", ambient[0], ambient[1], ambient[2]);
  printf("  - specular =\t(%lf,%lf,%lf)\n", specular[0], specular[1], specular[2]);
  printf("  - cartesian position =\t(%lf,%lf,%lf,%lf)\n", position[0], position[1], position[2],position[3]);
  printf("  - spherical position =\t(%lf,%lf,%lf)\n", getAlpha(), getBeta(), getRho());
  if (position[3]==0.0)
    printf("  - directional light\n");
  else
    printf("  - positional light\n");
  printf("  - constant attenuation =\t%lf\n", constatt);
  printf("  - linear attenuation =\t%lf\n", linatt);
  printf("  - quadratic attenuation =\t%lf\n", quadatt);
  printf("  - spot direction =\t(%lf,%lf,%lf)\n", spot_direction[0], spot_direction[1], spot_direction[2]);
  printf("  - spot cutoff =\t%lf\n", spot_cutoff);
  printf("  - spot exponent =\t%lf\n", spot_exponent);
}

// ================================================
//
// M O D I F I C A T I O N   D E S   P A R A M ET R E S
//
// D E   L A   S O U R C E   L U M I N E U S E
//
// ================================================

void
SooLight::setAmbient( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
  ambient[0] = r;
  ambient[1] = g;
  ambient[2] = b;
  ambient[3] = a;
}

void
SooLight::getAmbient( GLfloat &r, GLfloat &g, GLfloat &b, GLfloat &a )
{
  r = ambient[0];
  g = ambient[1];
  b = ambient[2];
  a = ambient[3];
}

void
SooLight::setDiffuse( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
  diffuse[0] = r;
  diffuse[1] = g;
  diffuse[2] = b;
  diffuse[3] = a;
}

void
SooLight::getDiffuse( GLfloat &r, GLfloat &g, GLfloat &b, GLfloat &a )
{
  r = diffuse[0];
  g = diffuse[1];
  b = diffuse[2];
  a = diffuse[3];
}

void
SooLight::setSpecular( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
  specular[0] = r;
  specular[1] = g;
  specular[2] = b;
  specular[3] = a;
}

void
SooLight::getSpecular( GLfloat &r, GLfloat &g, GLfloat &b, GLfloat &a )
{
  r = specular[0];
  g = specular[1];
  b = specular[2];
  a = specular[3];
}

void
SooLight::setPosition( GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
  position[0] = x;
  position[1] = y;
  position[2] = z;
  position[3] = w;
}

void
SooLight::getPosition( GLfloat &x, GLfloat &y, GLfloat &z, GLfloat &w )
{
  x = position[0];
  y = position[1];
  z = position[2];
  w = position[3];
}

void
SooLight::setAlpha( GLfloat value )
{
  GLfloat d = sqrt(position[0]*position[0]+position[1]*position[1]);
  GLfloat a = value * M_PI / 180;
  position[0] = d * cos(a);
  position[1] = d * sin(a);
}

GLfloat
SooLight::getAlpha()
{
  return 180*atan2(position[1],position[0])/M_PI;
}

void
SooLight::setBeta( GLfloat value )
{
  GLfloat alpha = atan2(position[1],position[0]);
  GLfloat beta = value * M_PI / 180;
  GLfloat r = sqrt(position[0]*position[0]+position[1]*position[1]+position[2]*position[2]);

  position[0] = r * sin(beta) * cos(alpha);
  position[1] = r * sin(beta) * sin(alpha);
  position[2] = r * cos(beta);
}

GLfloat
SooLight::getBeta()
{
  return 180*atan2(hypot(position[0],position[1]),position[2])/M_PI;
}

void
SooLight::setRho( GLfloat r )
{
  GLfloat alpha = atan2(position[1],position[0]);
  GLfloat beta = atan2(hypot(position[0],position[1]),position[2]);
  
  position[0] = r * sin(beta) * cos(alpha);
  position[1] = r * sin(beta) * sin(alpha);
  position[2] = r * cos(beta);
}

GLfloat
SooLight::getRho()
{
  return sqrt(position[0]*position[0]+position[1]*position[1]+position[2]*position[2]);
}

void
SooLight::setDirectional( int value )
{
  position[3] = (value)?0.0:1.0;
}

int
SooLight::getDirectional()
{
  return (position[3]==0.0);
}

void
SooLight::setConstantAttenuation( GLfloat a )
{
  constatt = a;
}

GLfloat
SooLight::getConstantAttenuation()
{
  return constatt;
}

void
SooLight::setLinearAttenuation( GLfloat a )
{
  linatt = a;
}

GLfloat
SooLight::getLinearAttenuation()
{
  return linatt;
}

void
SooLight::setQuadraticAttenuation( GLfloat a )
{
  quadatt = a;
}

GLfloat
SooLight::getQuadraticAttenuation()
{
  return quadatt;
}

void
SooLight::setSpotDirection( GLfloat x, GLfloat y, GLfloat z )
{
  spot_direction[0] = x;
  spot_direction[1] = y;
  spot_direction[2] = z;
}

void
SooLight::getSpotDirection( GLfloat &x, GLfloat &y, GLfloat &z )
{
  x = spot_direction[0];
  y = spot_direction[1];
  z = spot_direction[2];
}

void
SooLight::setSpotExponent( GLfloat a )
{
  spot_exponent = a;
}

GLfloat
SooLight::getSpotExponent()
{
  return spot_exponent;
}

void
SooLight::setSpotCutoff( GLfloat a )
{
  spot_cutoff = a;
}

GLfloat
SooLight::getSpotCutoff()
{
  return spot_cutoff;
}

int
SooLight::isOn()
{
  return on;
}

void
SooLight::isOn( int value )
{
  on = value;
}

void
SooLight::printShort(ostream &o)
{
  o << getName();
  o << "Number = " << number; 

  if (!getDisplay()) {o << "--"; return; }

  if (isOn())
    o << " (ON)";
  else
    o << " (OFF)";
}



