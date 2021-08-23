#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <stdio.h>
#include "SooPalette.h"

bool SooPalette::Load(const char * name)
{
  char ligne[200];
  FILE *f;
  float r, g, b;

  cout << "=> Lecture de " << name << " : "; fflush(stdout);
  f=fopen(name, "r");
  if (f == NULL)
  {
    printf("Fichier : %s inexistant\n", name);
    return false;
  }
  lut.clear();
  while (fgets(ligne,200,f))
    if ((strlen(ligne)>1)&&(!strstr(ligne,"#")))  // Lecture d'une couleur
      {
        sscanf(ligne, "%f %f %f", &r, &g, &b);
        lut.push_back(SooPaletteColor(r/255.0,g/255.0,b/255.0));
      }

  fclose(f);
  cout << lut.size() << " colors" << endl;
  return true;
}

void SooPalette::Print()
{
  cout << "Palette: " << endl;
  for (int i = 0; i < lut.size(); i++)
    cout << lut[i] << endl;
}

SooMaterial SooPalette::Material(double x, double transparency)
{
  SooMaterial material;

  int i = (int)ceil( ((double)lut.size() * x)/1.0 ) - 1;
  if (i>=lut.size())
    i = lut.size()-1;

  material.setAmbient(lut[i].red(), lut[i].green(), lut[i].blue());
  material.setDiffuse(lut[i].red(), lut[i].green(), lut[i].blue());
  material.setSpecular(0.296648, 0.296648, 0.296648);
  material.setShininess(0.088);
  material.setTransparency(transparency);
  return material;
}

SooColor SooPalette::Color(double x)
{
  SooColor color;

  int i = (int)ceil( ((double)lut.size() * x)/1.0 ) - 1;
  if (i>=lut.size())
    i = lut.size()-1;

  color.set(lut[i].red(), lut[i].green(), lut[i].blue());
  return color;
}
