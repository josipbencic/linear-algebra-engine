#ifndef LINEAR_SYSTEMS_HPP
#define LINEAR_SYSTEMS_HPP

#include <vector>

#include "../Constants.hpp"

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
    bool VerifyPrecompute(const mat& A) const;
  };


  /*  Cholesky decomposition. Requires matrix to be positive definite
      and symmetrical. Performs no checks. Works in O(n^3
  */
  class Cholesky {
    using mat = std::vector<std::vector<double>>;

  public:
    mat R;

    Cholesky(const mat& A);

    std::vector<double> Solve(const std::vector<double>& b) const;

  private:
    void PrecomputeR(const mat& A);
    bool VerifyPrecompute(const mat& A) const;
  };


  /*  A collection of simple brute force helper functions
      that are used to simplify implementations, but can also
      be used on their own outside this context.

      Since there is no big matrix implementation, 
      there are also helper functions to multiply, transpose matrices and
      check their equality.
      They are not optimised!
  */
  struct LinearSystemsUtil {
  private:
    using mat = std::vector<std::vector<double>>;

  public:
    static std::vector<double> SolveUpperTriangularSystem(
      const mat& U, const std::vector<double>& b);

    static std::vector<double> SolveLowerTriangularSystem(
      const mat& L, const std::vector<double>& b);

    /*  Works with non-quadratic matrices as well. */
    static mat Multiply(const mat& A, const mat& B);

    /*  Will act as if the first matrix was transposed. */
    static mat MultiplyTransposed(const mat& T, const mat& A);

    /*  Allows row permutation to be used on A matrix.
        Early exit on different dimensions.
    */
    static bool EqualWithRowPerm(
      const mat& A, const mat& B, double EPS = 1e-5,
      std::vector<int> P = std::vector<int>{});

    static mat Transpose(const mat& B);
  };
}

#endif