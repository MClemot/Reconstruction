// (c) Dominique Attali 2003 (LIS)

#ifndef __MISCMATH_H
#define __MISCMATH_H

#include <utility>

#ifndef MIN
#  define MIN(a,b) (((a)>(b))?(b):(a))
#endif

#ifndef MAX
#  define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#ifndef SGN
# define SGN(a) (((a)==0)?0:(((a)>0)?1:-1))
#endif

typedef std::pair<int,double> INT_WEIGHTED;
extern bool COMPARISON_INT_WEIGHTED(INT_WEIGHTED i, INT_WEIGHTED j);

extern void PrintBinary(int n);
extern void vectoriel(double * u, double * v, double * w);
extern int normalize(double * v);
extern int normal(double * a, double * b, double * c, double * n);
extern double scalaire(double * u, double * v);
extern void middle(double * a, double * b, double * m);
extern double distance(double * a, double * b);
extern void linear_interpolation(double * a, double * b, double * m, double ha, double hb, double hm);
extern void secure_linear_interpolation(double * a, double * b, double * m, double ha, double hb, double hm, double coef);

#endif
