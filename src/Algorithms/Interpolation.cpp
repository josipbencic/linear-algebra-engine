#include "Interpolation.hpp"

#include "../Core/Constants.hpp"

#include <vector>

using namespace std;

namespace math {

  LagrangeIP::LagrangeIP(const vector<pair<double, double>>& a)
    : A(a.size(), 0.0)
    , points(a) {
    Precompute();
  }

  void LagrangeIP::Precompute() {
    const int N = static_cast<int>(points.size());
    for (int i = 0; i < N; i++) {
      double omega_i = 1.0;
      for (int j = 0; j < N; j++) {
        if (i == j) {
          continue;
        }
        omega_i *= points[i].first - points[j].first;
      }
      A[i] = points[i].second / omega_i;
    }
  }

  double LagrangeIP::Evaluate(double u) const {
    //  Edge case: not having this would cause division with 0
    for (auto p : points) {
      if (abs(p.first - u) < EPSILON) {
        return p.second;
      }
    }

    double ans = 0.0;
    const int N = static_cast<int>(points.size());
    for (int k = 0; k < N; k++) {
      ans += A[k] / (u - points[k].first);
    }
    double omega = 1.0;
    for (auto p : points) {
      omega *= (u - p.first);
    }
    ans = ans / omega;
    return ans;
  }

  NewtonIP::NewtonIP(const vector<pair<double, double>>& p)
    : x(p.size())
    , f(p.size()) {
    for (unsigned i = 0; i < p.size(); i++) {
      x[i] = p[i].first;
      f[i] = p[i].second;
    }
    Precompute();
  }

  void NewtonIP::Precompute() {
    const int n = static_cast<int>(x.size());
    for (int i = 1; i < n; i++) {
      for (int j = n - 1; j >= i; j--) {
        f[j] = (f[j] - f[j - 1]) / (x[j] - x[j - i]);
      }
    }
  }

  double NewtonIP::Evaluate(double z) const {
    double ret = 0;
    const int n = static_cast<int>(x.size());
    for (int i = n - 1; i >= 0; i--) {
      ret = ret * (z - x[i]) + f[i];
    }
    return ret;
  }

}

