#include "InterpolationTests.hpp"


#include <sstream>
#include <utility>
#include <algorithm>
using namespace std;
using namespace math;

vector<double> LagrangeIPTests::solve(const string& testData, int testSize) {
  stringstream ss(testData);
  vector<pair<double, double>> v;
  for (int i = 0; i < 5; i++) {
    double x, y; ss >> x >> y;
    v.push_back({ x, y });
  }
  double x;
  ss >> x;
  LagrangeIP lagrange(v);
  vector<double> ret;
  ret.push_back(lagrange(x));
  return ret;
}

vector<double> NewtonIPTests::solve(const string& testData, int testSize) {
  stringstream ss(testData);
  vector<pair<double, double>> v;
  for (int i = 0; i < 5; i++) {
    double x, y; ss >> x >> y;
    v.push_back({ x, y });
  }
  double x;
  ss >> x;
  NewtonIP newton(v);
  vector<double> ret;
  ret.push_back(newton(x));
  return ret;
}
