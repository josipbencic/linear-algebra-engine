#include "LinearSystemsTests.hpp"

#include "../../src/Algorithms/LinearSystems.hpp"
#include "../../src/Constants.hpp"
using namespace math;

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

vector<double> CholeskyTests::solve(const string& testData, int testSize) {
  vector<vector<double>> X(testSize, vector<double>(testSize));
  stringstream matrixStream(testData);
  for (auto& row : X) {
    for (auto& x : row) {
      matrixStream >> x;
    }
  }

  CholeskyTests::Solver solver(X);

  vector<double> ret;
  ret.reserve(solver.R.size() * solver.R.size());
  for (auto& row : solver.R) {
    for (auto& x : row) {
      ret.push_back(x);
    }
  }
  return ret;
}


vector<double> LinearSolverLRTests::solve(const string& testData, int testSize) {
  vector<vector<double>> X(testSize, vector<double>(testSize));
  stringstream stream(testData);
  for (auto& row : X) {
    for (auto& x : row) {
      stream >> x;
    }
  }
  vector<double> b(testSize);
  for (auto& x : b) {
    stream >> x;
  }

  LinearSolverLRTests::Solver solver(X);

  return solver.Solve(b);
}
