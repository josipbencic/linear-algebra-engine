#ifndef INCLUDED_COMMON_FUNCTIONS_HPP
#define INCLUDED_COMMON_FUNCTIONS_HPP

#include "Constants.hpp"

namespace math {


  /*  There is a bug somewhere in the trig functions. This is uncommited! */
  /*  SIMD maybe?   */
  template <unsigned Iterations = 5, typename FIELD_TYPE = double>
  struct Sin {
    FIELD_TYPE operator ()(FIELD_TYPE x) const {
      while (x - PI_HALF > EPSILON) {
        x -= PI;
      }
      while (x + PI_HALF < EPSILON) {
        x += PI;
      }

      FIELD_TYPE sgn = 1;
      FIELD_TYPE cret = x;
      FIELD_TYPE cfact = 1.0;

      cout << "Sin factorials: ";
      FIELD_TYPE ret = x;
      for (unsigned i = 1; i < Iterations; ++i) {

        sgn *= -1;
        cfact *= static_cast<FIELD_TYPE>((2 * i) * (2 * i + 1));

        cret = cret * x * x / cfact;

        ret += sgn * cret;
      }
      return ret;
    }
  };

  template <unsigned Iterations = 5, typename FIELD_TYPE = double>
  struct Cos {
    FIELD_TYPE operator ()(FIELD_TYPE x) const {
      while (x - PI > EPSILON) {
        x -= PI;
      }
      while (x + PI < EPSILON) {
        x += PI;
      }
      FIELD_TYPE sgn = 1.0;
      FIELD_TYPE cfact = 1.0;
      FIELD_TYPE cret = 1.0;

      FIELD_TYPE ret = 1.0;
      for (unsigned i = 1; i < Iterations; ++i) {
        sgn *= -1.0;
        cfact *= static_cast<FIELD_TYPE>(2 * i * (2 * i - 1));
        cret = cret * x * x / cfact;
        ret += sgn * cret;
      }
      return ret;
    }
  };
}
#endif  