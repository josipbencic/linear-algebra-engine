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