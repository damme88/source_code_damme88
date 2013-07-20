#ifndef STRUCT_H_
#define STRUCT_H_
#include <cmath>

struct vector_t {
  union {
    struct {
      float x, y, z;
    };
    struct {
      float s, t, r;
    };
    float v[3];
  };

  vector_t() : x(0), y(0), z(0) {}          // constructor 1
  vector_t(float nx, float ny, float nz) :
   x(nx),
   y(ny),
   z(nz)
   {}  // constructor 2
  
  vector_t operator*(const float s) const {  // define operator *
    return vector_t(this->x * s, this->y * s, this->z * s);
  }

  void Normalize() {
    GLfloat length = sqrtf(x * x + y * y + z * z);  // length of vector normal for a point in OXYZ 
    if (length > 0.0f) {
      x /= length;
      y /= length;
      z /= length;
    }
  }
};

#endif