// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_LIGHT_H
#define __SOO_LIGHT_H

#include <cstdio>
#include <iostream>
#include <string>

#include "SooNode.h"

using namespace std;

// Classe implementant une source lumineuse a l'aide d'instructions OpenGL
//
// Une source lumineuse est formee de trois composantes qui definisse
// sa couleur :
//
//   - la lumiere ambiente `ambient'. Elle emane de la source
//   lumineuse. Mais apres plusieurs rebonds, il est impossible de
//   determiner de quelle direction elle vient. Cependant, si on
//   eteint la source lumineuse, elle disparait.
//
//   - la lumiere diffuse `diffuse'. Elle vient d'une direction
//   precise donnee par la position de la lumiere. Elle est d'autant
//   plus forte qu'elle frappe sous une incidence normale l'objet et
//   sera d'autant plus faible qu'elle rase l'objet. La lumiere
//   diffuse est reflechie dans toute les directions apres avoir
//   frappe la surface de l'objet.
//
//   - la lumiere speculaire `specular'. Elle vient d'une direction
//   particuliere et rebondit dans une direction preferentielle.
//
// La position de la lumiere est donnee par `position'. 
// La source lumineuse peut etre placee :
//
//   - soit a l'infinie en faisant `position[3] = 0.0'. La source
//   lumineuse est alors dite directionnelle. Pour une source
//   directionnelle, les rayons lumineux sont paralleles au moment ou
//   ils frappent l'objet.
//
//   - soit proche de la scene en faisant `position[3]=1.0'. La source
//   lumineuse est alors dite positionelle.
//
// Pour une source positionnelle, il est possible de definir
// l'attenuation de l'intensite lumineuse en fonction de la distance
// parcourue par les rayons. Celle-ci est modelisee en OpenGL par la
// formule :
// 
//        facteur d'attenuation = 1/(k_c + k_l * d + k_d * d * d)
//
// ou :
//       
//        d = distance parcourue par le rayon lumineux
//        k_c = `constatt' = terme constant d'attenuation
//        k_l = `linatt' = terme lineaire d'attenuation
//        k_q = `quadatt' = terme quadratique d'attenuation
//
// Une souce positionnelle peut se comporter comme un spot lumineux en
// restreignant la direction d'emission de la lumiere a un cone de
// demi-angle d'ouverture `spot_cutoff' compris entre [0,90.0]. Si
// `spot_cutoff = 180.0', la source lumineuse emet dans toutes les
// directions.  La direction du cone de lumiere est donnee par
// `spot_direction' Enfin, le parametre `spot_exponent' indique si la
// lumiere est plus ou moins concentre pres du centre du cone.
//
//
// Open GL donne la possibilite d'afficher jusqu'a 8 sources
// lumineuses differentes a la fois.


static int MAX_LIGHTS = 8;

class SooLight : public SooNode {
 private:
  static long lightmask; //available lights
  int number; 
  int on;
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat position[4];
  GLfloat constatt;
  GLfloat linatt;
  GLfloat quadatt;
  GLfloat spot_direction[3];
  GLfloat spot_exponent;
  GLfloat spot_cutoff;

 public:
  // ------------
  // Constructeur
  // ------------
  SooLight();

  // ------------
  // Destructeur
  // ------------
  ~SooLight();

  // --------------------------------------------
  // Parametres par defaut de la source lumineuse
  // --------------------------------------------
  void by_default();

  // -----------------------------------
  // Rendu openGL de la source lumineuse
  // -----------------------------------
  void drawArrow(GLfloat * position, GLfloat * color);

  void render();

  // -----------------------------------------------
  // Affichage des parametres de la source lumineuse
  // -----------------------------------------------
  void print();

  // --------------------------------------------------
  // Modification des parametres de la source lumineuse
  // --------------------------------------------------

  void setAmbient( GLfloat r, GLfloat g, GLfloat b, GLfloat a );
  void getAmbient( GLfloat &r, GLfloat &g, GLfloat &b, GLfloat &a );

  void setDiffuse( GLfloat r,GLfloat g, GLfloat b, GLfloat a );
  void getDiffuse( GLfloat &r, GLfloat &g, GLfloat &b, GLfloat &a );

  void setSpecular( GLfloat r,GLfloat g, GLfloat b, GLfloat a );
  void getSpecular( GLfloat &r, GLfloat &g, GLfloat &b, GLfloat &a );

  // Set and get cartesian coordinates
  void setPosition( GLfloat x, GLfloat y, GLfloat z, GLfloat w );
  void getPosition( GLfloat &x, GLfloat &y, GLfloat &z, GLfloat &w );

  // Set and get spherical coordinates
  void setAlpha( GLfloat value );
  GLfloat getAlpha();

  void setBeta( GLfloat value );
  GLfloat getBeta();

  void setRho( GLfloat value );
  GLfloat getRho();

  void setDirectional( int value );
  int getDirectional();

  void setSpotDirection( GLfloat x, GLfloat y, GLfloat z );
  void getSpotDirection( GLfloat &x, GLfloat &y, GLfloat &z );

  void setSpotExponent( GLfloat value );
  GLfloat getSpotExponent();

  void setSpotCutoff( GLfloat value );
  GLfloat getSpotCutoff();

  void setConstantAttenuation( GLfloat a );
  GLfloat getConstantAttenuation();

  void setLinearAttenuation( GLfloat a );
  GLfloat getLinearAttenuation();

  void setQuadraticAttenuation( GLfloat a );
  GLfloat getQuadraticAttenuation();

  int isOn();
  void isOn( int value );

  void printShort(ostream &o);
};

#endif /* __SOO_LIGHT_H */
