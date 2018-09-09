#include "CommonFunctions.hpp"
#include "AlgebraicStructures/Surface.hpp"
#include "AlgebraicStructures/Polynomial.hpp"
#include "AlgebraicStructures/Polynomial2.hpp"
#include "Algorithms/LinearSystems.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;
using namespace math;


void testTrig(double from = -1000.0, double to = -1000.0, double inc = 1.0) {
  Sin<35, double> jsin;
  Cos<35, double> jcos;
  constexpr double eps = std::numeric_limits<double>::epsilon();

  for (double x = from; x < to; x += inc) {
    double canssin = sin(x);
    auto janssin = jsin(x);
    auto sindif = std::abs(canssin - janssin);

    double canscos = cos(x);
    auto janscos = jcos(x);
    auto cosdif = std::abs(canscos - janscos);

    cout << setprecision(10);
    if (sindif > eps) {
      cout << "Sin error at " << x << " by " << sindif << endl;
      if (sindif > 1.0) {
        cout << canssin << " " << janssin << endl;
      }
    }

    if (cosdif > eps) {
      cout << "Cos error at " << x << " by " << cosdif << endl;
      if (cosdif > 1.0) {
        cout << canscos << " " << janscos << endl;
      }
    }
  }
}

int main() {
  //testTrig(rad(-90), rad(180), rad(3));

  vector<vector<double>> A(4, vector<double>(4));
  stringstream stream("1 -1 0 1 -1 3 -1 2 2 -4 0 6 1 3 -1 3");
  for (auto& r : A) {
    for (auto& x : r) {
      stream >> x;
    }
  }

  LinearSolverLR solver(A);
  stringstream vecstream("");
  vector<double> b;
  double x;
  while (vecstream >> x) {
    b.push_back(x);
  }
  auto solution = solver.Solve(b);
  for (auto& z : solution) {
    cout << z << " ";
  }
  cout << endl;
  getchar();
}