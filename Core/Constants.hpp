#ifndef MATH_CONSTANTS_HPP
#define MATH_CONSTANTS_HPP

#include <limits>

namespace math {

  enum class ESpaces {
    R3 = 0,
    R4 = 1,
    R5 = 2,
    POLY2 = 3,
    POLY3 = 4,
    POLY4 = 5,
    M33 = 6,
    LINEARSYSTEM = 7
  };

  constexpr double ROOT_OF_2 =          1.41421356;
  constexpr double PI =                 3.14159265359;
  constexpr double PI_DIV_180 =         0.01745329251;
  constexpr double PI_DIV_180_INVERSE = 57.2957795131;
  constexpr double PI_HALF =            PI / 2.0;

  constexpr double EPSILON =            std::numeric_limits<double>::epsilon();


  inline double rad(double deg) {
    return deg * PI_DIV_180;
  }

  inline double deg(double rad) {
    return rad * PI_DIV_180_INVERSE;
  }

  template <unsigned D>
  class Polynomial;

  template <unsigned D>
  using Poly = Polynomial<D>;

  template <unsigned D, typename FIELD_TYPE>
  class Polynomial2;

  template <unsigned D>
  using Poly2 = Polynomial2<D, double>;
}

#endif
