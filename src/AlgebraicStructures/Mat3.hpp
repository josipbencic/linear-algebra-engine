#ifndef MAT3_HPP
#define MAT3_HPP

#include "../Constants.hpp"

#include <cmath>
#include <cstring>

namespace math {

  class M33 {

    //  TODO: MATRIX - VECTOR MULTIPLICATION
    //friend inline vec3 operator* (const mat3& mat, const vec3& vec);

    friend inline M33 operator* (double alpha, const M33& matrix);
    friend inline M33 operator* (const M33& matrix, double alpha);
    friend inline M33 operator* (const M33& left, const M33& right);
    friend inline M33 operator+ (const M33& a, const M33& b);
    friend inline M33 operator- (const M33& a, const M33& b);

    friend inline M33 transpose(const M33& a);
    friend inline double trace(const M33 &a);
    friend inline double inner_product(const M33 &a, const M33 &b);

  public:
    M33() {
      memset(data, 0, sizeof(data));
    }

    M33(const double matrix[][3]) {
      
      data[0] = matrix[0][0];
      data[1] = matrix[0][1];
      data[2] = matrix[0][2];
      data[3] = matrix[1][0];
      data[4] = matrix[1][1];
      data[5] = matrix[1][2];
      data[6] = matrix[2][0];
      data[7] = matrix[2][1];
      data[8] = matrix[2][2];
    }

    M33(double x) {
      for (unsigned i = 0; i < 9; i++)
        data[i] = 0;
      data[0] = data[4] = data[8] = x;
    }

    M33(const M33& src) {
      for (unsigned i = 0; i < 9; i++)
        data[i] = src.data[i];
    }

    M33& operator= (const M33& rhs) {
      for (unsigned i = 0; i < 9; i++)
        data[i] = rhs.data[i];
      return *this;
    }

    M33 operator -() {

      M33 ret;
      for (unsigned i = 0; i < 9; i++)
        ret.data[i] = 0 - data[i];
      return ret;
    }
    
    const M33& normalize() {

      double norm = sqrt(inner_product(*this, *this));
      for (unsigned i = 0; i < 9; i++)
        data[i] = data[i] / norm;

      return *this;
    }

    bool operator ==(const M33& rhs) {
      bool ret = true;
      for (unsigned i = 0; i < 9; i++)
        ret = ret && (abs(rhs.data[i] - data[i]) < EPSILON);
      return ret;
    }

    double data[9];
  };

  inline M33 operator-(const M33& a, const M33& b) {
    M33 ret;
    for (unsigned i = 0; i < 9; i++)
      ret.data[i] = a.data[i] - b.data[i];
    return ret;
  }

  inline M33 operator+(const M33& a, const M33& b) {
    M33 ret;
    for (unsigned i = 0; i < 9; i++)
      ret.data[i] = a.data[i] + b.data[i];
    return ret;
  }

  inline M33 operator*(const M33& left, const M33& right) {
    M33 ret;
    for (unsigned i = 0; i < 3; i++)
      for (unsigned j = 0; j < 3; j++)
        for (unsigned k = 0; k < 3; k++)
          ret.data[i * 3 + j] += left.data[i * 3 + k] * right.data[k * 3 + j];
    return ret;
  }
  
  inline M33 transpose(const M33 &a) {

    M33 ret = a;
    ret.data[1] = a.data[3];
    ret.data[3] = a.data[1];
    ret.data[2] = a.data[6];
    ret.data[6] = a.data[2];
    ret.data[5] = a.data[7];
    ret.data[7] = a.data[5];
    return ret;
  }

  inline double trace(const M33 &a) {
    return a.data[0] + a.data[4] + a.data[8];
  }

  inline double inner_product(const M33& a, const M33& b) {
    return trace(a * transpose(b));
  }

  inline M33 operator* (double alpha, const M33& A) {
    M33 ret = A;
    for (int i = 0; i < 9; i++)
      ret.data[i] *= alpha;
    return ret;
  }

  inline M33 operator* (const M33& A, double alpha) {
    return operator*(alpha, A);
  }
}

#endif