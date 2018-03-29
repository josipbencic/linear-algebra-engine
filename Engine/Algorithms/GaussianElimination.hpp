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

  /*  LR Algorithm. Send matrix to precompute L and R, then solve systems
      Ax = b, for any vector b.
  */
  class LinearSolverLR {        
    /*  To save space, both matrices are stored inside one. This is possible
        because L matrix has only 1s on its diagonal and zeros above it, while
        R has zeros below diagonal.
    */
    using mat = std::vector<std::vector<double>>;
    

    /*  Permutation matrix is stored as a permutation ordering.
        It is needed since the algorithm uses partial pivoting to enable higher stability.
    */
    std::vector<int> P;

  public:
    mat LR;
    LinearSolverLR(const mat& A);

    std::vector<double> Solve(const std::vector<double>& b) const;

  private:
    void PrecomputeLR(const mat& A);
  };
}

#endif