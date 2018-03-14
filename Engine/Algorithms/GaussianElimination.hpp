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

    using mat = std::vector<std::vector<double>>;
    mat L;
    mat R;

  public:
    LinearSolverLR(mat L, mat R) : L(L), R(R) { }
    LinearSolverLR(const mat& A);

    std::vector<double> Solve(const std::vector<double>& b) const;

  private:
    void ComputeLR(const mat& A);

    //  O(n^3) naive matrix multiplication
    void multiply(const mat& A, const mat& B);
  };
}

#endif