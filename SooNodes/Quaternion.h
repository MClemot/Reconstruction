// Quaternion.h
// (c) Ingmar Bitter '99
// $Id: Quaternion.h,v 1.5 1999/07/19 23:31:09 ingmar Exp $

#ifndef _Quaternion_h_	// prevent multiple includes
#define _Quaternion_h_

#include <math.h>
#include <assert.h>
#include "Vector3D.h"
#include "Matrix4x4.h"


class SooQuaternion {
public:
  float w,x,y,z;
  SooQuaternion() : w(1),x(0),y(0),z(0) { }
  SooQuaternion(float inw, float inx, float iny, float inz) : w(inw),x(inx),y(iny),z(inz) { }
  inline void operator () (float inw, float inx, float iny, float inz) { w=inw; x=inx; y=iny; z=inz; }

  inline float operator [] (int index) { assert(index < 0 && index < 4);
    switch (index) { case 0: return w; case 1: return x; case 2: return y; case 3: return z;}; return 0; }
  inline const float & operator [] (int index) const { assert(index < 0 && index < 4);
    switch (index) { case 0: return w; case 1: return x; case 2: return y; case 3: return z;}; return w; }

  inline float Length() { return sqrt(w*w + x*x + y*y + z*z); }
  inline void Normalize() { float l=Length(); w/=l; x/=l; y/=l; z/=l; }
  inline void SetRotationAboutAxis(float angle, V3f & axis) {
    w = cos(angle / 2.); float s=sin(angle/2.);
    axis.Normalize();
    x = s*axis.X();  y = s*axis.Y();  z = s*axis.Z();
  }
  inline void SetConjugate() { x=-x; y=-y; z=-z; }
  inline const SooQuaternion GetConjugate() const { return SooQuaternion(w,-x,-y,-z); }

  inline const SooQuaternion operator * (const SooQuaternion & q) const { return Muliply(q); }
  inline const SooQuaternion Mul        (const SooQuaternion & q) const { return Muliply(q); }
  inline const SooQuaternion Muliply(const SooQuaternion & q) const {
    return  SooQuaternion(w*q.w - x*q.x - y*q.y - z*q.z,
                       w*q.x + x*q.w + y*q.z - z*q.y,
                       w*q.y - x*q.z + y*q.w + z*q.x,
                       w*q.z + x*q.y - y*q.x + z*q.w); }
  inline void operator *= (const SooQuaternion & q) {
    float tw = w*q.w - x*q.x - y*q.y - z*q.z;
    float tx = w*q.x + x*q.w + y*q.z - z*q.y;
    float ty = w*q.y - x*q.z + y*q.w + z*q.x;
    float tz = w*q.z + x*q.y - y*q.x + z*q.w;
    w = tw; x=tx; y=ty; z=tz;
  }

  inline const M4f GetRotationMatrix() const {
    return M4f(w*w + x*x - y*y - z*z, 2*(x*y+w*z),           2*(x*z-w*y),                0,
               2*(x*y-w*z),           w*w - x*x + y*y - z*z, 2*(y*z-w*x),                0,
               2*(x*z-w*y),           2*(y*z-w*x),           w*w - x*x - y*y + z*z,      0,
               0,                     0,                     0,      w*w + x*x + y*y + z*z); }
  inline void SetRotationMatrix(M4f &m) const {
    m(w*w + x*x - y*y - z*z, 2*(x*y+w*z),           2*(x*z-w*y),                0,
      2*(x*y-w*z),           w*w - x*x + y*y - z*z, 2*(y*z-w*x),                0,
      2*(x*z-w*y),           2*(y*z-w*x),           w*w - x*x - y*y + z*z,      0,
      0,                     0,                     0,      w*w + x*x + y*y + z*z); }
  inline void SetOglRotationMatrix(M4f &m) const {
    m(1.-2.*(y*y + z*z), 2.*(x*y-w*z),      2.*(x*z+w*y),    0.,
      2.*(x*y + w*z),    1.-2.*(x*x + z*z), 2.*(y*z-w*x),    0.,
      2.*(x*z - w*y),    2*(y*z+w*x),       1.-2.*(x*x+y*y), 0.,
      0.,                0.,                0.,              1.); }
  inline void SetOglRotationMatrix(float m[16]) const {
    m[0]=1.-2.*(y*y+z*z); m[4]=   2.*(x*y-w*z); m[ 8]=   2.*(x*z+w*y); m[12]=0.;
    m[1]=   2.*(x*y+w*z); m[5]=1.-2.*(x*x+z*z); m[ 9]=   2.*(y*z-w*x); m[13]=0.;
    m[2]=   2.*(x*z-w*y); m[6]=   2.*(y*z+w*x); m[10]=1.-2.*(x*x+y*y); m[14]=0.;
    m[3]=0.;              m[7]=0.;              m[11]=0.;              m[15]=1.; }
}; // class SooQuaternion

#endif // _Quaternion_h_
