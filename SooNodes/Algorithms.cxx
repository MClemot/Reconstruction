#include <CGAL/squared_distance_3.h> //for 3D functions
#include <CGAL/Triangle_3.h>
#include <CGAL/Vector_3.h>
#include "Algorithms.h"

void OffsetTriangle(Point_3 * a, double param)
{
  Vector_3 u[3];
  Vector_3 v[3];
  double l[3];

  for (int i = 0; i < 3; i++)
    u[i] = (a[(i+1)%3] - a[i]) / sqrt( squared_distance(a[i], a[(i+1)%3]));

  for (int i = 0; i < 3; i++)
    l[i] = sqrt(2) / sqrt( 1 + u[i] * u[(i+2)%3] );

  for (int i = 0; i < 3; i++)
    {
      v[i] = u[i] - u[(i+2)%3];
      v[i] = v[i] / sqrt( v[i].squared_length() );
      a[i] = a[i] + param * l[i] * v[i];
    }
}

void Write(ostream& o, vector<Point_3> & cloud)
{
  std::vector<Point_3>::iterator it;

  for (it = cloud.begin() ; it != cloud.end(); ++it)
    o << "v " << *it << endl;
}

bool Load(vector<Point_3> & cloud, const char * name)
{
  char ligne[200];
  FILE *f;
  double x, y, z;

  cout << "=> Lecture de " << name << " : "; fflush(stdout);
  f=fopen(name, "r");
  if (f == NULL)
  {
    printf("Fichier : %s inexistant\n", name);
    return false;
  }
  cloud.clear();
  while (fgets(ligne,200,f))
    if ((strlen(ligne)>=1)&&(ligne[0]=='v'))  // Lecture d'un sommet
      {
        sscanf(ligne, "v %lf %lf %lf", &x, &y, &z);
        cloud.push_back(CGAL::Simple_cartesian<double>::Point_3(x,y,z));
      }

  fclose(f);
  cout << cloud.size() << " points" << endl;
  return true;
}

bool Load(vector<Point_3> & vertices, vector<vector<int>> & triangles, const char * name)
{
  char ligne[200];
  FILE *f;
  vector<int> triangle;
  double x,y,z;
  int a,b,c;

  cout << "=> Lecture de " << name << " : " << endl;
  f=fopen(name, "r");
  if (f == NULL)
    {
      printf("Fichier : %s inexistant\n", name);
      return false;
    }

  vertices.clear();
  for (vector<vector<int>>::iterator iter = triangles.begin(); iter != triangles.end(); iter++)
    (*iter).clear();
  triangles.clear();

  triangle.clear();
  triangle.resize(3);
  while (fgets(ligne,200,f))
    if ((strlen(ligne)>=1)&&(ligne[0]=='v'))  // Lecture d'un sommet
      {
        sscanf(ligne, "v %lf %lf %lf", &x, &y, &z);
        vertices.push_back(CGAL::Simple_cartesian<double>::Point_3(x,y,z));
      }
    else if ((strlen(ligne)>=1)&&(ligne[0]=='f'))  // Lecture d'un triangle
      {
        sscanf(ligne, "f %d %d %d", &a, &b, &c);
        triangle[0] = a-1; triangle[1] = b-1; triangle[2] = c-1;
        triangles.push_back(triangle);
      }

  fclose(f);

  cout << vertices.size() << " vertices" << endl;
  cout << triangles.size() << " triangles" << endl;
  return true;
}


double DistanceToNearest(vector<Point_3> & cloud, Point_3 & p)
{
  double d, dmin;
  for (int i = 0; i<cloud.size(); i++)
    {
      d = sqrt( squared_distance(cloud[i],p) );
      if ((i==0) || ((i>0) && (dmin > d)))
        dmin = d;
    }
  return dmin;
}

