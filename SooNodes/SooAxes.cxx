// (c) Dominique Attali 2003 (LIS)

#include <string>

#include "SooAxes.h"

SooAxes::SooAxes() : SooDrawable( "Axis" )
{
  by_default();
}

void
SooAxes::by_default()
{
  setUnit(1.0);
}

void
SooAxes::draw()
{
  float epsilon = 1.0/16.0*size;

  // L'axe des X
  glBegin(GL_LINES);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(size,0.0,0.0);
  glVertex3f(size+epsilon, -epsilon, epsilon);
  glVertex3f(size+epsilon, epsilon, -epsilon);
  glVertex3f(size+epsilon, -epsilon, -epsilon);
  glVertex3f(size+epsilon, epsilon, epsilon);
  glEnd();

  // L'axe des Y
  glBegin(GL_LINES);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,size,0.0);
  glVertex3f(epsilon ,size+epsilon, epsilon);
  glVertex3f(0.0 ,size+epsilon, 0.0);
  glVertex3f(-epsilon ,size+epsilon, epsilon);
  glVertex3f(epsilon ,size+epsilon, -epsilon);
  glEnd();

  // L'axe des Z
  glBegin(GL_LINES);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,size);
  glVertex3f(-epsilon,-epsilon,size+epsilon);  
  glVertex3f(epsilon,-epsilon,size+epsilon);  
  glVertex3f(epsilon,-epsilon,size+epsilon);  
  glVertex3f(-epsilon,epsilon,size+epsilon);  
  glVertex3f(-epsilon,epsilon,size+epsilon);  
  glVertex3f(epsilon,epsilon,size+epsilon);  
  glEnd();  
}

void
SooAxes::setUnit(double u)
{
  size = u;
  touch();
}

double
SooAxes::getUnit()
{
  return size;
}
