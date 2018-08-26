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

void test_NewtonIP1() {
  stringstream ss("0 -3 1 -4 2 -7 4 -115 5 -268");
  vector<pair<double, double>> v;
  for (int i = 0; i < 5; i++) {
    double x, y; ss >> x >> y;
    v.push_back({ x, y });
  }
  NewtonIP nw(v);
  for (auto x : nw.x) {
    cout << x << " ";
  }
  cout << endl;
  for (auto f : nw.f) {
    cout << f << " ";
  }
  cout << endl;
}