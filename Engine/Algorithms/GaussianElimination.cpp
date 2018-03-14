#include "GaussianElimination.hpp"

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
namespace math {

  vector<double> GaussianElimination(vector<vector<double>> v) {
    //  Row Echelon form
    auto n = static_cast<int>(v[0].size());
    for (int iter = 0; iter < n - 2; ++iter) {

      //  if the current pivot is zerox
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
    ComputeLR(A);
  }

  vector<double> LinearSolverLR::Solve(const vector<double>& b) const {
    assert(L.size() == b.size());
    assert(R.size() == b.size());
    assert(L[0].size() == b.size());
    assert(R[0].size() == b.size());

    int n = static_cast<int>(b.size());

    //  Solve Ly = b
    vector<double> y = b;
    for (int i = 0; i < n; i++) {
      double tmp_sum = 0.0;
      for (int j = 0; j < i; j++) {
        tmp_sum += L[i][j] * y[j];
      }
      y[i] -= tmp_sum;
      y[i] /= L[i][i];
    }

    //  Solve Lx = y
    vector<double> x = y;
    for (int i = n - 1; i >= 0; i--) {
      double tmp_sum = 0.0;
      for (int j = i + 1; j < n; j++) {
        tmp_sum += R[i][j] * x[j];
      }
      x[i] -= tmp_sum;
      x[i] /= R[i][i];
    }
    return x;
  }

  void LinearSolverLR::ComputeLR(const mat& A) {
    //  Adjust sizes
    L.resize(A.size());
    R.resize(A.size());
    for (unsigned i = 0; i < A.size(); ++i) {
      L[i].resize(A.size());
      R[i].resize(A.size());
    }

    //  TODO
  }
}
