#include "GaussianElimination.hpp"

#include <iostream>
#include <vector>

using namespace std;
namespace math {

  /*
    DOESN'T WORK YET!

    Fails on equations which have 0-coefficients!
  */
  vector<double> GaussianElimination(vector<vector<double>> v) {

    vector<double> ret;

    //  Row Echelon form
    auto n = static_cast<int>(v[0].size());
    for (int iter = 0; iter < n - 2; ++iter) {
      for (int i = iter + 1; i < n - 1; ++i) {
        for (int j = n - 1; j >= iter; --j) {
          v[i][j] -= v[iter][j] * v[i][iter] / v[iter][iter];
        }
      }
    }

    int m = static_cast<int>(v.size());

    //  Reduced Row Echelon form
    for (int iter = n - 2; iter >= 0; --iter) {
      for (int i = 0; i < iter; ++i) {
        v[i][n - 1] -= v[iter][n - 1] * v[i][iter] / v[iter][iter];
        v[i][iter] = 0.0;
      }
    }

    //  Get results
    for (int i = 0; i < m; i++)
      ret.push_back(v[i][m] / v[i][i]);

    return ret;
  }
}

/*
#include "Engine\Algorithms\GaussianElimination.hpp"

int main() {
std::vector<std::vector<double> > v{
{1, 3, 5}, {2, 1, 5}};

std::vector<double> ans = math::GaussianElimination(v);
for (unsigned i = 0; i < ans.size(); i++)
std::cout << ans[i] << " ";
std::cout << std::endl;

getchar();
}
*/