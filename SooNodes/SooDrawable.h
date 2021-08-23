// (c) Dominique Attali 2003 (LIS)

// ================================================
//
// Classe Drawable
//
// Permet de memoriser une liste Open GL
//
// ================================================

#ifndef __SOO_DRAWABLE_H
#define __SOO_DRAWABLE_H

#include <stdio.h>
#include "SooNode.h"

// ================================================
//
// Classe SooDrawable
//
// ================================================

class SooDrawable : public SooNode
{
private:
  static int listIndex;
  int list;
  int must_be_updated;

  // ----- FONCTIONS POUR MODIFIER LA LISTE
  // ----- ELLES SONT PRIVEES !!!
  // Vide la liste
  void Empty()
    { glDeleteLists(list,1); } 

public:
  // ------------
  // Constructeur
  // ------------
  SooDrawable(const string n);

  // -----------
  // Destructeur
  // -----------
  ~SooDrawable();

  // -----------------
  // Render the object
  // -----------------
  void render();
  
  // ----------------------
  // How to draw the object
  // Fonction virtuelle devant etre redefinie dans les classes
  // derivee.
  // ----------------------
  virtual void draw() = 0;

  // --------------------------------------
  // Procedure affichant le nom de la liste
  // --------------------------------------
  virtual void print();

  // --------------------------------------------------
  // Modification des parametres d'un drawable
  // --------------------------------------------------
  void touch();
};

#endif
