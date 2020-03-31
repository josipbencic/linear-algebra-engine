#ifndef REALCOORDINATESPACE_HPP
#define REALCOORDINATESPACE_HPP

#include "../Constants.hpp"

#include <initializer_list>
#include <algorithm>
#include <cstring>
#include <cmath>

namespace math {

  template <std::size_t DIMENSION, typename REAL_TYPE = double>
  class Rn {

    friend Rn<DIMENSION, REAL_TYPE> operator +(
        const Rn<DIMENSION, REAL_TYPE> &op1, const Rn<DIMENSION, REAL_TYPE> &op2) {

      Rn<DIMENSION, REAL_TYPE> ret;
      for (std::size_t i = 0; i < DIMENSION; i++) {
        ret.component[i] = op1.component[i] + op2.component[i];
      }
      return ret;
    }

    friend Rn<DIMENSION, REAL_TYPE> operator -(
      const Rn<DIMENSION, REAL_TYPE> &op1, const Rn<DIMENSION, REAL_TYPE> &op2) {

      Rn<DIMENSION, REAL_TYPE> ret;
      for (std::size_t i = 0; i < DIMENSION; i++) {
        ret.component[i] = op1.component[i] - op2.component[i];
      }
      return ret;
    }

    friend double inner_product(
      const Rn<DIMENSION, REAL_TYPE> &op1, const Rn<DIMENSION, REAL_TYPE> &op2) {

      double ret = 0.0f;
      for (std::size_t i = 0; i < DIMENSION; i++) {
        ret += op1.component[i] * op2.component[i];
      }
      return ret;
    }

    friend inline Rn<DIMENSION, REAL_TYPE> operator *(
      double alpha, const Rn<DIMENSION, REAL_TYPE> &op) {

      Rn<DIMENSION, REAL_TYPE> ret;
      for (std::size_t i = 0; i < DIMENSION; i++) {
        ret.component[i] = alpha * op.component[i];
      }
      return ret;

    }

    friend inline Rn<DIMENSION, REAL_TYPE> operator *(const Rn<DIMENSION, REAL_TYPE> &op, double alpha) {
      return alpha * op;
    }

  public:

    double component[DIMENSION];


    Rn() {
      std::memset(component, 0, sizeof(component));
    }

    Rn(const Rn<DIMENSION> &src) {
      std::copy_n(src.component, DIMENSION, component);
    }

    Rn(const Rn<DIMENSION, float> &src) {
      std::copy_n(src.component, DIMENSION, component);
    }

    Rn(REAL_TYPE newCoords[]) {
      std::copy_n(newCoords, DIMENSION, component);
    }

    /*  Relatively slow. Use in playground. */
    Rn(std::initializer_list<REAL_TYPE>&& src) {
      for (std::size_t i = 0; i < DIMENSION; i++) {
        if (src.size() > i) {
          component[i] = *(begin(src) + i);
        }
        else {
          component[i] = 0;
        }
      }
    }

    const Rn<DIMENSION, REAL_TYPE> operator -() {
      Rn<DIMENSION, REAL_TYPE> ret;
      for (std::size_t i = 0; i < DIMENSION; i++) {
        ret.component[i] = -component[i];
      }
      return ret;
    }

    bool operator ==(const Rn<DIMENSION, REAL_TYPE>& rhs) {

      for (std::size_t i = 0; i < DIMENSION; i++) {
        if (std::abs(component[i] - rhs.component[i]) < EPSILON) {
          return false;
        }
      }
      return true;
    }

    Rn<DIMENSION, REAL_TYPE>& normalize() {

      //  cannot divide by zero!
      if (*this == Rn<DIMENSION, REAL_TYPE>()) {
        return *this;
      }

      double norm = std::sqrt(inner_product(*this, *this));
      for (std::size_t i = 0; i < DIMENSION; i++) {
        component[i] = component[i] / norm;
      }
      
      return *this;
    }
  };
}

#endif
