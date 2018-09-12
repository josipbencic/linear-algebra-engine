#include "Tester.hpp"

#include "../src/Algorithms/LinearSystems.hpp"
#include "../src/Algorithms/Interpolation.hpp"
#include "../src/MathStreams.hpp"
using namespace math;

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
using namespace std;

Tester::Tester() {
  auto choleskyTests = createTests<CholeskyTests>();
  tests.insert(begin(choleskyTests), end(choleskyTests));

  auto lrTests = createTests<LinearSolverLRTests>();
  tests.insert(begin(lrTests), end(lrTests));

  auto newtonIPTests = createTests<NewtonIPTests>();
  tests.insert(begin(newtonIPTests), end(newtonIPTests));

  auto lagrangeIPTests = createTests<LagrangeIPTests>();
  tests.insert(begin(lagrangeIPTests), end(lagrangeIPTests));
}

bool Tester::run() {
  cout << "Running tests..." << endl;
  bool ans = true;
  for (auto& x : tests) {
    cout << x.first << " ";
    if (!x.second()) {
      cout << "--> failed." << endl;
      ans = false;
    }
    else {
      cout << "--> passed." << endl;
    }
  }
  if (ans) {
    cout << "Tests succeeded." << endl;
  }
  else {
    cout << "Tests failed." << endl;
  }
  return ans;
}
