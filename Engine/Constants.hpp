#ifndef MATH_CONSTANTS_HPP
#define MATH_CONSTANTS_HPP

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

  const double ROOT_OF_2 =          1.41421356;
  const double PI =                 3.14159265359;
  const double PI_DIV_180 =         0.01745329251;
  const double PI_DIV_180_INVERSE = 57.2957795131;
  const double EPSILON =            1e-9;


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
