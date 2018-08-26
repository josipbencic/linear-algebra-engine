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

inline std::vector<std::vector<double>> createMatrixFromString(string str, int size) {
  const int testMatrixDim = (int)sqrt(size);
  vector<vector<double>> X(testMatrixDim, vector<double>(testMatrixDim));
  stringstream matrixStream(str);
  for (auto& row : X) {
    for (auto& x : row) {
      matrixStream >> x;
    }
  }
  return X;
}

vector<vector<double>> CholeskyTests::transformInput(const string& testData, int testSize) {
  return createMatrixFromString(testData, testSize);
}

vector<double> CholeskyTests::transformSolution(const Cholesky& solver) {
  vector<double> ret;
  ret.reserve(solver.R.size() * solver.R.size());
  for (auto& row : solver.R) {
    for (auto& x : row) {
      ret.push_back(x);
    }
  }
  return ret;
}

