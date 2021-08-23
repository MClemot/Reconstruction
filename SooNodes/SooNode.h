// (c) Dominique Attali 2003 (LIS)

#ifndef __SOO_NODE_H
#define __SOO_NODE_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <FL/glu.h>
#include <string>
#include <map>

using namespace std;

class SooNode;
typedef map<GLuint, SooNode *>   MapPtrSooNode;
extern SooNode * findPtrSooNode(GLuint key);

/**
 * Classe de base pour toutes les autres classes SooXXX.
 *
 * La classe comprend trois fonctions virtuelles :
 *   - render()
 *   - by_default()
 *   - le destructeur
 */

class SooNode
{
 private:
  string name; /**< Chaque noeud a un nom */
  int display; /**< Indique si le noeud doit être affiché ou pas */
  static GLuint key_max; /**< Indique le nombre de noeuds créés pour l'instant */

 protected:
  GLuint key; /**< Chaque noeud comprend une clé permettant de l'identifier de façon unique */

 public:
  static MapPtrSooNode map; /**< Map permettant de mettre de retrouver l'adresse du noeud à partir de sa clé */

 protected:
  void setName(const string n);

 public:

  /** @name Constructors / Destructors / Initialization
   */
  //@{
  SooNode(const string n);
  virtual ~SooNode(){};
  virtual void by_default() {};
  //@}

  /** @name Printing
   */
  //@{
  string getName();
  virtual void printShort(ostream& o);
  virtual void printSubTree(int n);
  void printTree();
  friend ostream& operator << (ostream& o, const SooNode & node);
  //@}

  /** @name Display
   */
  //@{
  void setDisplay(int d);
  int getDisplay();
  void changeDisplay();
  virtual void render() = 0;
  virtual void touch() {}
  //@}
};



#endif
