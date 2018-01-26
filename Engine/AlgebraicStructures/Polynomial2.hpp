#ifndef INCLUDED_POLYNOMIAL_2
#define INCLUDED_POLYNOMIAL_2

#include "RealCoordinateSpace.hpp"

#include <initializer_list>
#include <cstring>

namespace math {

  /*  2 - variable polynomial is represented with matrix of coefficients.
      Only the lower trianglar part is filled with coefficients.
  */
  struct PolyUtil {

    template <typename FIELD_TYPE = double>
    static inline FIELD_TYPE fastExp(FIELD_TYPE base, unsigned exp) {
      FIELD_TYPE Base = base;
      FIELD_TYPE Ret = 1;
      while (exp) {
        if (exp & 1) Ret = Ret * Base;
        Base = Base * Base;
        exp >>= 1;
      }
      return Ret;
    }
  };


  template <unsigned D, typename FIELD_TYPE = double>
  class Polynomial2 {
  public:
    FIELD_TYPE coefficient[D + 1][D + 1];

    Polynomial2() {
      memset(coefficient, 0, sizeof(coefficient));
    }

    /*  Slow. Use only in playground. 
        Coeff. are in order: xn, x^(n-1)y, x^(n-2)y...
    */
    Polynomial2(const std::initializer_list<FIELD_TYPE>& list) {
      for (size_t i = 0; i <= D; i++) {
        for (size_t j = 0; j <= D; j++) {
          if ((i * (D + 1) + j) < list.size()) {
            coefficient[i][j] = *(begin(list) + i * (D + 1) + j);
          }
          else {
            coefficient[i][j] = 0.0;
          }
        }
      }
    }

    inline FIELD_TYPE operator ()(Rn<2, FIELD_TYPE> x) const {
      return this->operator()(x.component[0], x.component[1]);
    }

    FIELD_TYPE operator ()(FIELD_TYPE x, FIELD_TYPE y) const {
      FIELD_TYPE Ret = 0;
      for (size_t i = 0; i <= D; i++) {
        for (size_t j = 0; j <= D; j++) {
          Ret += coefficient[i][j] * PolyUtil::fastExp(x, i) * PolyUtil::fastExp(y, j);
        }
      }
      return Ret;
    }
  };
}


#endif
