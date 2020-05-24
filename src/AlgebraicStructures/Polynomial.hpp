#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include "../Constants.hpp" // EPSILON

#include <cmath>   // sqrt
#include <cstring> // memset
#include <initializer_list>

namespace math {

/*  Class representation of polynomial of fixed degree.
 */
template <unsigned DEGREE> class Polynomial {
public:
  Polynomial() { memset(coefficients, 0, sizeof(coefficients)); }

  Polynomial(double coefficients_[]) { copyCoefficients(coefficients_); }

  /*  Client needs to supply an initializer list with enough elements.
   */
  Polynomial(std::initializer_list<double> src) {
    memset(coefficients, 0, sizeof(coefficients));
    size_t j = 0;
    for (auto i = src.begin(); i != src.end() && (i - src.begin()) <= DEGREE;
         i++) {
      coefficients[j++] = *i;
    }
  }

  Polynomial(const Polynomial<DEGREE> &src) {
    copyCoefficients(src.coefficients);
  }

  const Polynomial<DEGREE> &operator=(const Polynomial<DEGREE> &rhs) {

    if (rhs == *this)
      return *this;
    for (size_t i = 0; i <= DEGREE; i++)
      coefficients[i] = rhs[i];
    return *this;
  }

  Polynomial(const Polynomial<DEGREE> &&rhs) {
    copyCoefficients(rhs.coefficents);
    memset(rhs.coefficients, 0, sizeof(rhs.coefficients));
  }

  const Polynomial<DEGREE> &operator=(const Polynomial<DEGREE> &&rhs) {
    copyCoefficients(rhs.coefficents);
    memset(rhs.coefficients, 0, sizeof(rhs.coefficients));
  }

  static unsigned degree() { return DEGREE; }

  const double &operator[](size_t at) const { return coefficients[at]; }

  double &operator[](size_t at) { return coefficients[at]; }

  /*  Compares polynomials on their coefficients.
    Runs in O(DEGREE).
  */
  bool operator==(const Polynomial<DEGREE> &p) const {

    for (size_t i = 0; i < DEGREE; i++)
      if (abs(p[i] - coefficients[i]) > EPSILON)
        return false;
    return true;
  }

  /*  Returns polynomial's value in a given argument
    Uses Horner's algorithm for fast evaluation in O(DEGREE)
  */
  double evaluate(double x) {

    double y = coefficients[DEGREE];
    for (int i = static_cast<int>(DEGREE - 1); i >= 0; --i)
      y = y * x + coefficients[i];
    return y;
  }

  inline double norm() const { return norm(*this); }

  Polynomial<DEGREE> &normalize() {

    double norm_ = sqrt(inner_product(*this, *this));
    for (size_t i = 0; i <= DEGREE; i++)
      coefficients[i] /= norm_;
    return *this;
  }

private:
  inline void copyCoefficients(const double coefficients__[]) {
    for (size_t i = 0; i <= DEGREE; i++)
      this->coefficients[i] = coefficients__[i];
  }

  double coefficients[DEGREE + 1];
};

/*  Operands need to be declared of same degree. Client can zero-out
  non-wanted coefficients, if lower-degree polynomial is needed.

  Operations that currently work:
  Addition and subtraction with other polynomials (group structure).
  Also, it is possible to retrieve a negated element of given polynomial.
  Multiplication with inner_product (vector space).
  Addition and subtraction with reals (free coefficient is changed).
  Scalar product (inner product space).

  To be added:
  Division, Remainder and Greatest Common Divisor algorithm on polynomials.
*/

/*  Addition and subtraction. */
template <unsigned DEGREE_>
inline const Polynomial<DEGREE_> operator+(const Polynomial<DEGREE_> &op1,
                                           const Polynomial<DEGREE_> &op2) {

  Polynomial<DEGREE_> ret;
  for (size_t i = 0; i <= DEGREE_; i++)
    ret[i] = op1[i] + op2[i];
  return ret;
}

template <unsigned DEGREE_>
inline const Polynomial<DEGREE_> operator+(const Polynomial<DEGREE_> &p,
                                           double alpha) {

  Polynomial<DEGREE_> ret(p);
  ret[0] + alpha;
  return ret;
}

template <unsigned DEGREE_>
inline const Polynomial<DEGREE_> operator+(double alpha,
                                           const Polynomial<DEGREE_> &p) {
  return p + alpha;
}

template <unsigned DEGREE_>
inline const Polynomial<DEGREE_> operator-(const Polynomial<DEGREE_> &op1,
                                           const Polynomial<DEGREE_> &op2) {

  Polynomial<DEGREE_> ret;
  for (size_t i = 0; i <= DEGREE_; i++)
    ret[i] = op1[i] - op2[i];
  return ret;
}

template <unsigned DEGREE_>
inline const Polynomial<DEGREE_> operator-(const Polynomial<DEGREE_> &p,
                                           double alpha) {

  Polynomial<DEGREE_> ret(p);
  ret[0] -= alpha;
  return ret;
}

template <unsigned DEGREE_>
inline const Polynomial<DEGREE_> operator-(double alpha,
                                           const Polynomial<DEGREE_> &p) {
  return p - alpha;
}

template <unsigned DEGREE_>
inline const Polynomial<DEGREE_> operator-(const Polynomial<DEGREE_> &p) {

  Polynomial<DEGREE_> ret;
  for (size_t i = 0; i <= DEGREE_; i++)
    ret[i] = -p[i];
  return ret;
}

/*  Multiplication by inner_product.
 */
template <unsigned DEGREE_>
const inline Polynomial<DEGREE_> operator*(double alpha,
                                           const Polynomial<DEGREE_> &p) {

  Polynomial<DEGREE_> ret;
  for (size_t i = 0; i <= DEGREE_; i++)
    ret[i] = p[i] * alpha;
  return ret;
}

template <unsigned DEGREE_>
const inline Polynomial<DEGREE_> operator*(const Polynomial<DEGREE_> &p,
                                           double alpha) {
  return alpha * p;
}

/*  Polynomial multiplication. Returns a polynomial of double the
  degree of given polynomials.
  Runs in O(DEGREE_ ^ 2).
*/
template <unsigned DEGREE_>
const inline Polynomial<2 * DEGREE_> operator*(const Polynomial<DEGREE_> &p,
                                               const Polynomial<DEGREE_> &q) {

  Polynomial<2 * DEGREE_> ret;
  for (size_t i = 0; i <= 2 * DEGREE_; i++)
    for (size_t j = 0; j <= i; j++)
      ret[i] += p[j] * q[i - j];
  return ret;
}

/*  Polynomial derivative. Will return polynomial
  of the SAME degree (highest coeff. will be zeroed).
*/
template <unsigned DEGREE_>
const inline Polynomial<DEGREE_> derivative(const Polynomial<DEGREE_> &p) {

  Polynomial<DEGREE_> ret;
  for (size_t i = 0; i <= DEGREE_ - 1; i++)
    ret[i] = p[i + 1] * (i + 1);
  ret[DEGREE_ - 1] = 0.0;
  return ret;
}

/*  Polynomial integration on a given range.
 */
template <unsigned DEGREE_>
const inline double integrate(const Polynomial<DEGREE_> &p, double from,
                              double to) {

  Polynomial<DEGREE_ + 1> temp;
  for (size_t i = 0; i <= DEGREE_; i++)
    temp[i + 1] = p[i] / (i + 1);
  return temp.evaluate(to) - temp.evaluate(from);
}

/*  Default inner product on polynomials.
  Integral on range [-1, 1] of product of given polynomials.
*/
template <unsigned DEGREE_>
double inner_product(const Polynomial<DEGREE_> &op1,
                     const Polynomial<DEGREE_> &op2) {

  return integrate(op1 * op2, -1.0, 1.0);
}

/*  Returns polynomial norm, as defined canonicaly in normed space
  with inner product.

  NOTE: Norm is *always* a real number. Even when dealing above complex field.
*/
template <unsigned DEGREE_> double norm(const Polynomial<DEGREE_> &p) {
  return sqrt(inner_product(p, p));
}

/*  Will normalize given polynomial and return a reference to it.
  Function *WILL NOT* work for zero polynomial. Algorithm that
  uses the function needs to watch for that.
*/
template <unsigned DEGREE_>
Polynomial<DEGREE_> &normalize(const Polynomial<DEGREE_> &p) {

  double norm_ = norm(p);
  for (size_t i = 0; i <= DEGREE_; i++) {
    p[i] /= norm_;
  }
  return p;
}
} // namespace math
#endif
