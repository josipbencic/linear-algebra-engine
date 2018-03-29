#include "GaussianElimination.hpp"

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

  LinearSolverLR::LinearSolverLR(const mat& A) {
    PrecomputeLR(A);
  }

  vector<double> LinearSolverLR::Solve(const vector<double>& b) const {
    assert(LR.size() == b.size());
    assert(LR[0].size() == b.size());

    int n = static_cast<int>(b.size());

    //  Apply permutation P to b
    vector<double> y(n, 0.0);
    for (int i = 0; i < n; i++) {
      y[i] = b[P[i]];
    }

    //  Solve Ly = b
    for (int i = 0; i < n; i++) {
      double tmp_sum = 0.0;
      for (int j = 0; j < i; j++) {
        tmp_sum += LR[i][j] * y[j];
      }
      y[i] -= tmp_sum;
    }

    //  Solve Lx = y
    vector<double> x = y;
    for (int i = n - 1; i >= 0; i--) {
      double tmp_sum = 0.0;
      for (int j = i + 1; j < n; j++) {
        tmp_sum += LR[i][j] * x[j];
      }
      x[i] -= tmp_sum;
      x[i] /= LR[i][i];
    }
    return x;
  }

  bool check(const vector<vector<double>>& LR, const vector<vector<double>>& A, 
      const vector<int>& P) {
    const int n = static_cast<int>(LR.size());
    auto L = vector<vector<double>>(n, vector<double>(n, 0.0));
    auto R = vector<vector<double>>(n, vector<double>(n, 0.0));
    auto X = vector<vector<double>>(n, vector<double>(n, 0.0));
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

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          X[i][j] += L[i][k] * R[k][j];
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (abs(X[i][j] - A[P[i]][j]) > 1e-5) {
          return false;
        }
      }
    }
    return true;
  }

  void LinearSolverLR::PrecomputeLR(const mat& A) {
    const int n = static_cast<int>(A.size());
    LR = A;
    P.resize(n);
    for (int i = 0; i < n; ++i) {
      P[i] = i;
    }

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
        cout << "Swapping? " << P[j] << " and " << P[max_pos] << endl;
        swap(P[j], P[max_pos]);
        swap(LR[j], LR[P[j]]);
      }

      for (int i = j + 1; i < n; i++) {
        float scalar = LR[i][j] / LR[j][j];
        cout << "Cancelling scalar for " << i << " " << j << " is " << scalar << endl;
        //  Switching sign here, instead of taking an inverse later
        LR[i][j] = scalar;

        for (int k = j + 1; k < n; k++) {
          LR[i][k] = LR[i][k] - scalar * LR[j][k];
        }
      }
    }
    assert(check(LR, A, P));
  }
}
