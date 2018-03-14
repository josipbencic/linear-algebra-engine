#ifndef GAUSSIAN_ELIMINATION_HPP
#define GAUSSIAN_ELIMINATION_HPP

#include <vector>

#include "../../Engine/Constants.hpp"

namespace math {

  /*  Assuming the matrix is has full rank (and is quadratic).
      This is NOT LR algorithm. It's a simple Gaussian elimination,
      similar to the one done with pen and paper.
      Pivoting is implemented with equation swapping.
  */
  std::vector<double> GaussianElimination(std::vector<std::vector<double>> v);
}

#endif