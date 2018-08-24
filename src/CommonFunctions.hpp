#ifndef INCLUDED_COMMON_FUNCTIONS_HPP
#define INCLUDED_COMMON_FUNCTIONS_HPP

#include "Constants.hpp"

/*  SIMD maybe?   */

namespace math {

  /*  Takes argument in radians. */
  template <unsigned Iterations = 5, typename FIELD_TYPE = double>
  struct Sin {
    FIELD_TYPE operator ()(FIELD_TYPE x) const {
      FIELD_TYPE sgn = 1;
      FIELD_TYPE cx = x;
      FIELD_TYPE cfact = 1.0;

      FIELD_TYPE ret = x;
      for (unsigned i = 1; i < Iterations; ++i) {
        sgn *= -1;
        cfact *= static_cast<FIELD_TYPE>(2 * i) * static_cast<FIELD_TYPE>(2 * i + 1);
        cx *= x * x;

        ret += sgn * cx / cfact;
      }
      return ret;
    }
  };

  /*  Takes argument in radians. */
  template <unsigned Iterations = 5, typename FIELD_TYPE = double>
  struct Cos {
    FIELD_TYPE operator ()(FIELD_TYPE x) const {
      FIELD_TYPE sgn = 1.0;
      FIELD_TYPE cx = 1.0;
      FIELD_TYPE cfact = 1.0;

      FIELD_TYPE ret = 1.0;
      for (unsigned i = 1; i < Iterations; ++i) {
        sgn *= -1.0;
        cfact *= static_cast<FIELD_TYPE>(2 * i) * static_cast<FIELD_TYPE>(2 * i - 1);
        cx *= x * x;
        ret += sgn * cx / cfact;
      }
      return ret;
    }
  };
}
#endif
