#ifndef REALCOORDINATESPACE_HPP
#define REALCOORDINATESPACE_HPP

namespace math {

  template <size_t DIMENSION>
  class Rn {

    friend Rn<DIMENSION> operator +(
        const Rn<DIMENSION> &op1, const Rn<DIMENSION> &op2) {

      Rn<DIMENSION> ret;
      for (size_t i = 0; i < DIMENSION; i++) {
        ret.component[i] = op1.component[i] + op2.component[i];
      }
      return ret;
    }

    friend Rn<DIMENSION> operator -(
      const Rn<DIMENSION> &op1, const Rn<DIMENSION> &op2) {

      Rn<DIMENSION> ret;
      for (size_t i = 0; i < DIMENSION; i++) {
        ret.component[i] = op1.component[i] - op2.component[i];
      }
      return ret;
    }

    friend double inner_product(
      const Rn<DIMENSION> &op1, const Rn<DIMENSION> &op2) {

      double ret = 0.0f;
      for (size_t i = 0; i < DIMENSION; i++) {
        ret += op1.component[i] * op2.component[i];
      }
      return ret;
    }

    friend inline Rn<DIMENSION> operator *(
      double alpha, const Rn<DIMENSION> &op) {

      Rn<DIMENSION> ret;
      for (size_t i = 0; i < DIMENSION; i++) {
        ret.component[i] = alpha * op.component[i];
      }
      return ret;

    }

    friend inline Rn<DIMENSION> operator *(const Rn<DIMENSION> &op, double alpha) {
      return alpha * op;
    }

  public:

    double component[DIMENSION];


    Rn() {
      memset(component, 0, sizeof(component));
    }

    Rn(const Rn<DIMENSION> &src) {
      copy_n(src.component, DIMENSION, component);
    }

    Rn(const double newCoords[]) {
      copy_n(newCoords, DIMENSION, component);
    }

    const Rn<DIMENSION> operator -() {
      Rn<DIMENSION> ret;
      for (size_t i = 0; i < DIMENSION; i++) {
        ret.component[i] = -component[i];
      }
      return ret;
    }

    bool operator ==(const Rn<DIMENSION>& rhs) {

      for (size_t i = 0; i < DIMENSION; i++) {
        if (abs(component[i] - rhs.component[i]) < EPSILON) {
          return false;
        }
      }
      return true;
    }

    Rn<DIMENSION>& normalize() {

      //  cannot divide by zero!
      if (*this == Rn<DIMENSION>()) {
        return *this;
      }

      double norm = sqrt(inner_product(*this, *this));
      for (size_t i = 0; i < DIMENSION; i++) {
        component[i] = component[i] / norm;
      }
      
      return *this;
    }
  };
}

#endif
