#include "LinearSystems.hpp"

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

namespace math {

  vector<double> GaussianElimination(vector<vector<double>> v) {
    //  Row Echelon form
    auto n = static_cast<int>(v[0].size());
    for (int iter = 0; iter < n - 2; ++iter) {

      //  if the current pivot is zero
      //  replace the current row with the row that has an
      //  element with max value on pivot position
      if (abs(v[iter][iter]) < EPSILON) {
        int max_pivot = iter;
        double max_value = abs(v[iter][iter]);
        for (int j = iter + 1; j < n - 1; j++) {
          if (abs(v[j][iter]) > max_value) {
            max_pivot = j;
            max_value = abs(v[j][iter]);
          }
          swap(v[j], v[iter]);
        }
        assert(abs(v[iter][iter]) > EPSILON);
      }

      for (int i = iter + 1; i < n - 1; ++i) {
        for (int j = n - 1; j >= iter; --j) {
          v[i][j] -= v[iter][j] * v[i][iter] / v[iter][iter];
        }
      }
    }

    //  Reduced Row Echelon form
    for (int iter = n - 2; iter >= 0; --iter) {
      for (int i = 0; i < iter; ++i) {
        v[i][n - 1] -= v[iter][n - 1] * v[i][iter] / v[iter][iter];
      }
    }

    //  Get results
    vector<double> ret(n - 1, 0);
    for (int i = 0; i < n - 1; i++) {
      ret[i] = v[i][n - 1] / v[i][i];
    }
    return ret;
  }

  LinearSolverLR::LinearSolverLR(const mat& A)
    : LR(A)
    , P(A.size()) {

    for (unsigned i = 0; i < A.size(); ++i) {
      P[i] = i;
    }
    PrecomputeLR(A);
  }

  bool LinearSolverLR::VerifyPrecompute(const mat& A) const {
    const int n = static_cast<int>(LR.size());
    auto L = vector<vector<double>>(n, vector<double>(n, 0.0));
    auto R = vector<vector<double>>(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
      L[i][i] = 1.0;
      for (int j = 0; j < i; j++) {
        L[i][j] = LR[i][j];
      }
    }
    for (int j = 0; j < n; j++) {
      for (int i = 0; i <= j; i++) {
        R[i][j] = LR[i][j];
      }
    }

    auto X = LinearSystemsUtil::Multiply(L, R);
    return LinearSystemsUtil::EqualWithRowPerm(A, X, 1e-5, P);
  }

  void LinearSolverLR::PrecomputeLR(const mat& A) {
    const int n = static_cast<int>(A.size());

    for (int j = 0; j < n - 1; j++) {
      //  Partial pivoting
      {
        int max_pos = j;
        double max_val = abs(LR[j][j]);
        for (int i = j + 1; i < n; i++) {
          if (abs(LR[i][j]) - abs(max_val) > EPSILON) {
            max_val = abs(LR[i][j]);
            max_pos = i;
          }
        }
        // cout << "Swapping? " << P[j] << " and " << P[max_pos] << endl;
        swap(P[j], P[max_pos]);
        swap(LR[j], LR[P[j]]);
      }

      for (int i = j + 1; i < n; i++) {
        double scalar = LR[i][j] / LR[j][j];
        // cout << "Cancelling scalar for " << i << " " << j << " is " << scalar << endl;
         //  Switching sign here, instead of taking an inverse later
        LR[i][j] = scalar;

        for (int k = j + 1; k < n; k++) {
          LR[i][k] = LR[i][k] - scalar * LR[j][k];
        }
      }
    }
    assert(VerifyPrecompute(A));
  }

  vector<double> LinearSolverLR::Solve(const vector<double>& b) const {
    assert(LR.size() == b.size());
    assert(LR[0].size() == b.size());

    int n = static_cast<int>(b.size());

    //  Apply permutation P to b
    vector<double> pb(n, 0.0);
    for (int i = 0; i < n; i++) {
      pb[i] = b[P[i]];
    }
    auto y = LinearSystemsUtil::SolveLowerTriangularSystem(LR, pb);
    auto x = LinearSystemsUtil::SolveUpperTriangularSystem(LR, y);
    return x;
  }

  Cholesky::Cholesky(const mat& A)
    : R(A.size(), vector<double>(A.size(), 0.0)) {
    PrecomputeR(A);
  }

  void Cholesky::PrecomputeR(const mat& A) {
    int n = static_cast<int>(A.size());
    for (int i = 0; i < n; i++) {
      {
        double S = 0.0;
        for (int k = 0; k < i; k++) {
          S += R[k][i] * R[k][i];
        }
        R[i][i] = sqrt(A[i][i] - S);
      }
      for (int j = i + 1; j < n; j++) {
        double S = 0.0;
        for (int k = 0; k < i; k++) {
          S += R[k][i] * R[k][j];
        }
        R[i][j] = (1 / R[i][i]) * (A[i][j] - S);
      }
    }
    VerifyPrecompute(A);
  }

  bool Cholesky::VerifyPrecompute(const mat& A) const {
    auto X = LinearSystemsUtil::MultiplyTransposed(R, R);
    return LinearSystemsUtil::EqualWithRowPerm(X, A);
  }

  vector<double> Cholesky::Solve(const vector<double>& b) const {
    auto RT = LinearSystemsUtil::Transpose(R);
    auto y = LinearSystemsUtil::SolveLowerTriangularSystem(RT, b);
    auto x = LinearSystemsUtil::SolveUpperTriangularSystem(R, y);
    return x;
  }

  // =======================================================================
  // ============  Utilities  ==============================================
  // =======================================================================


  vector<double> LinearSystemsUtil::SolveUpperTriangularSystem(
    const mat& U, const vector<double>& y
  ) {
    const int n = static_cast<int>(U.size());
    vector<double> x = y;
    for (int i = n - 1; i >= 0; i--) {
      double tmp_sum = 0.0;
      for (int j = i + 1; j < n; j++) {
        tmp_sum += U[i][j] * x[j];
      }
      x[i] -= tmp_sum;
      x[i] /= U[i][i];
    }
    return x;
  }

  vector<double> LinearSystemsUtil::SolveLowerTriangularSystem(
    const mat& L, const vector<double>& y
  ) {
    const int n = static_cast<int>(L.size());
    auto x = y;
    //  Solve Ly = b
    for (int i = 0; i < n; i++) {
      double tmp_sum = 0.0;
      for (int j = 0; j < i; j++) {
        tmp_sum += L[i][j] * x[j];
      }
      x[i] -= tmp_sum;
    }
    return x;
  }

  LinearSystemsUtil::mat LinearSystemsUtil::Multiply(
    const mat& L, const mat& R
  ) {
    const int m = static_cast<int>(L.size());
    const int n = static_cast<int>(R.size());
    const int l = static_cast<int>(R[0].size());

    mat X(m, vector<double>(l, 0.0));

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < l; j++) {
        for (int k = 0; k < n; k++) {
          X[i][j] += L[i][k] * R[k][j];
        }
      }
    }
    return X;
  }

  LinearSystemsUtil::mat LinearSystemsUtil::MultiplyTransposed(
    const mat& T, const mat& A
  ) {
    const int m = static_cast<int>(T.size());
    const int n = static_cast<int>(T[0].size());
    const int l = static_cast<int>(A[0].size());

    mat X(m, vector<double>(l, 0.0));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < l; j++) {
        for (int k = 0; k < m; k++) {
          X[i][j] += T[k][i] * T[k][j];
        }
      }
    }
    return X;
  }

  bool LinearSystemsUtil::EqualWithRowPerm(
    const mat& A, const mat& X, double EPS, vector<int> P
  ) {
    if (A.size() != X.size() || A[0].size() != X[0].size()) {
      return false;
    }
    const int n = static_cast<int>(A.size());
    const int m = static_cast<int>(A[0].size());

    if (P == vector<int>{}) {
      P.resize(n);
      for (int i = 0; i < n; i++) {
        P[i] = i;
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (abs(X[i][j] - A[P[i]][j]) > EPS) {
          return false;
        }
      }
    }
    return true;
  }

  LinearSystemsUtil::mat LinearSystemsUtil::Transpose(const mat& B) {
    const int n = static_cast<int>(B.size());
    vector<vector<double>> X(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        X[j][i] = B[i][j];
      }
    }
    return X;
  }

}
