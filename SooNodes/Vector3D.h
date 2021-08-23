// Vector3D.h
// (c) Ingmar Bitter '96-'99
// $Id: Vector3D.h,v 1.8 1999/08/24 19:19:53 ingmar Exp $

#ifndef _Vector3D_h_	// prevent multiple includes
#define _Vector3D_h_

#include <math.h>

template <class T> class Vector3D {
public:
	T e[3];

public:

  // constructors & destructors
  inline Vector3D<T> () { e[0] = e[1] = e[2] = 0; }

  inline Vector3D<T> (const Vector3D<T> & v)
    {
      e[0]= static_cast<T>(v.e[0]);
      e[1]= static_cast<T>(v.e[1]);
      e[2]= static_cast<T>(v.e[2]);
    }

  inline Vector3D<T> (const T & x, const T & y, const T & z)
    { e[0]=x; e[1]=y; e[2]=z; }


#if 0
  // !!!!!! Cette fonction ne passe pas au compilateur gcc installe
  // sur Silicon
  template <class C> inline Vector3D<T> (const Vector3D<C> & v)
    {
      e[0]= static_cast<T>(v.e[0]);
      e[1]= static_cast<T>(v.e[1]);
      e[2]= static_cast<T>(v.e[2]);
    }
#endif

  inline double Norm  ( )       const { return sqrt(X()*X() + Y()*Y() + Z()*Z()); }
  inline double SquareLength( ) const { return     (X()*X() + Y()*Y() + Z()*Z()); }
  inline double Length( )       const { return sqrt(X()*X() + Y()*Y() + Z()*Z()); }
  inline Vector3D<T> & Normalize ( );

	inline T X() const { return e[0]; }
	inline T Y() const { return e[1]; }
	inline T Z() const { return e[2]; }

	inline T U() const { return e[0]; }
	inline T V() const { return e[1]; }
	inline T W() const { return e[2]; }

	inline T R() const { return e[0]; }
	inline T G() const { return e[1]; }
	inline T B() const { return e[2]; }

	inline T & X() { return e[0]; }
	inline T & Y() { return e[1]; }
	inline T & Z() { return e[2]; }

	inline T & U() { return e[0]; }
	inline T & V() { return e[1]; }
	inline T & W() { return e[2]; }

	inline T & R() { return e[0]; }
	inline T & G() { return e[1]; }
	inline T & B() { return e[2]; }

	inline T & operator [] (const int index)       { return e[index]; }
	inline T   operator [] (const int index) const { return e[index]; }

	inline Vector3D<T> & operator()(const T x, const T y, const T z) { e[0]=x; e[1]=y; e[2]=z;  return *this; }

  // computation functions
  inline bool operator == (const Vector3D<T> &v) const { return ( X()==v.X() && Y()==v.Y() && Z()==v.Z() ); }
  inline bool operator != (const Vector3D<T> &v) const { return ( X()!=v.X() || Y()!=v.Y() || Z()!=v.Z() ); }

  inline Vector3D<T> operator + () const { return *this; }
  inline Vector3D<T> operator - () const { return Vector3D<T>(-X(), -Y(), -Z()); }

  inline Vector3D<T>   operator +  (const Vector3D<T> & v) const { return Vector3D<T>(X()+v.X(), Y()+v.Y(), Z()+v.Z()); }
  inline Vector3D<T>   operator -  (const Vector3D<T> & v) const { return Vector3D<T>(X()-v.X(), Y()-v.Y(), Z()-v.Z()); }
  inline Vector3D<T> & operator += (const Vector3D<T> & v) { X()+=v.X(); Y()+=v.Y(); Z()+=v.Z(); return *this;  }
  inline Vector3D<T> & operator -= (const Vector3D<T> & v) { X()-=v.X(); Y()-=v.Y(); Z()-=v.Z(); return *this;  }

  inline friend Vector3D<T> operator * (const T & a, const Vector3D<T> & v) { return v*a; }
  inline Vector3D<T>   operator *  (const T & a) const { return Vector3D<T>(X()*a, Y()*a, Z()*a); }
  inline Vector3D<T>   operator /  (const T & a) const { return Vector3D<T>(X()/a, Y()/a, Z()/a); }
  inline Vector3D<T> & operator *= (const T & a) { X()*=a; Y()*=a; Z()*=a; return *this; }
  inline Vector3D<T> & operator /= (const T & a) { X()/=a; Y()/=a; Z()/=a; return *this; }

  inline T Dot        (const Vector3D<T> & v) const { return DotProduct(v); }
  inline T DotProduct (const Vector3D<T> & v) const { return (X()*v.X() + Y()*v.Y() + Z()*v.Z()); }
 
  inline Vector3D<T> Cross       (const Vector3D<T> v) const { return CrossProduct(v); }
  inline Vector3D<T> CrossProduct(const Vector3D<T> v) const { return Vector3D(Y()*v.Z() - Z()*v.Y(), Z()*v.X() - X()*v.Z(), X()*v.Y() - Y()*v.X()); }

}; // class Vector3D

typedef Vector3D<char>   V3c;
typedef Vector3D<short>  V3s;
typedef Vector3D<int>    V3i;
typedef Vector3D<long>   V3l;
typedef Vector3D<float>  V3f;
typedef Vector3D<double> V3d;

template <class T> Vector3D<T> & Vector3D<T>::Normalize ( ) { 
  double length = sqrt(X()*X() + Y()*Y() + Z()*Z()); 
  if (length > 0) *this /= length; return *this;
} // Normalize

#endif // $Id: Vector3D.h,v 1.8 1999/08/24 19:19:53 ingmar Exp $
