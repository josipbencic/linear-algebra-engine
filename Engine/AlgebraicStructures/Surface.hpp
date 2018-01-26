#ifndef INCLUDED_SURFACE_HPP
#define INCLUDED_SURFACE_HPP

#include "RealCoordinateSpace.hpp"

namespace math {

  template <typename F1, typename F2, typename F3, typename REAL_TYPE = double>
  class Surface {
  public:
    F1 f1;
    F2 f2;
    F3 f3;

    Surface() = default;


    Surface(F1 &&f1, F2 &&f2, F3 &&f3)
      : f1(std::move(f1)) , f2(std::move(f2)), f3(std::move(f3)) { }

    inline const Rn<3, REAL_TYPE> operator ()(Rn<2> x) const {
      return this->operator()(x.component[0], x.component[1]);
    }

    inline const Rn<3, REAL_TYPE> operator ()(REAL_TYPE u, REAL_TYPE v) const {
      return Rn<3, REAL_TYPE>({f1(u, v), f2(u, v), f3(u, v)});
    }
  };
}

#endif
