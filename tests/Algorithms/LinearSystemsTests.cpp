#include <gtest/gtest.h>

#include "../../src/Algorithms/LinearSystems.hpp"
#include "../../src/Constants.hpp"

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <vector>

auto matrixFromString(const std::string &str, const size_t size) {
  auto X = std::vector<std::vector<double>>(size, std::vector<double>(size));
  auto matrixStream = std::stringstream(str);
  for (auto &row : X) {
    for (auto &x : row) {
      matrixStream >> x;
    }
  }
  return X;
}

auto vectorFromString(const std::string &str) {
  auto x = std::vector<double>();
  auto stream = std::stringstream(str);
  double tmp;
  while (stream >> tmp) {
    x.push_back(tmp);
  }
  return x;
}

TEST(LinearSystemsTests, Cholesky1) {
  const auto X = std::vector<std::vector<double>>{
      {9, 0, 0, 3}, {0, 16, 8, -4}, {0, 8, 13, -2}, {3, -4, -2, 18}};
  const auto Y = std::vector<std::vector<double>>{
      {3, 0, 0, 1}, {0, 4, 2, -1}, {0, 0, 3, 0}, {0, 0, 0, 4}};
  auto solver = math::Cholesky{X};
  for (std::size_t i = 0; i < solver.R.size(); i++) {
    for (std::size_t j = 0; j < solver.R.size(); j++) {
      ASSERT_DOUBLE_EQ(Y[i][j], solver.R[i][j]);
    }
  }
}

TEST(LinearSystemsTests, Cholesky2) {
  const auto X = std::vector<std::vector<double>>{
      {4, -2, 14, 6}, {-2, 17, -23, -3}, {14, -23, 66, 21}, {6, -3, 21, 34}};
  const auto Y = std::vector<std::vector<double>>{
      {2, -1, 7, 3}, {0, 4, -4, 0}, {0, 0, 1, 0}, {0, 0, 0, 5}};
  auto solver = math::Cholesky{X};
  for (std::size_t i = 0; i < solver.R.size(); i++) {
    for (std::size_t j = 0; j < solver.R.size(); j++) {
      ASSERT_DOUBLE_EQ(Y[i][j], solver.R[i][j]);
    }
  }
}

TEST(LinearSystemsTests, LR1) {
  constexpr double EPS = 1e-5;
  auto A = std::vector<std::vector<double>>{{1, 1, 5}, {4, 2, 1}, {6, 3, 1}};
  auto b = std::vector<double>{1, 1, 7};
  auto x_expected = std::vector<double>{-50, 106, -11};
  auto solver = math::LinearSolverLR{A};
  auto x = solver.Solve(b);
  for (std::size_t i = 0; i < x.size(); i++) {
    ASSERT_NEAR(x[i], x_expected[i], EPS);
  }
}

TEST(LinearSystemsTests, LR2) {
  constexpr double EPS = 1e-5;
  auto A = std::vector<std::vector<double>>{
      {1, -1, 0, 1}, {-1, 3, -1, 2}, {2, -4, 0, 6}, {1, 3, -1, 3}};
  auto b = std::vector<double>{1, 1, 1, 7};
  auto x_expected = std::vector<double>{2.5, 2.5, 6, 1};
  auto solver = math::LinearSolverLR{A};
  auto x = solver.Solve(b);
  for (std::size_t i = 0; i < x.size(); i++) {
    ASSERT_NEAR(x[i], x_expected[i], EPS);
  }
}

TEST(LinearSystemsTests, LR3) {
  constexpr double EPS = 1e-5;
  auto A = std::vector<std::vector<double>>{
      {0, 0, 2, 2}, {2, 2, 4, 2}, {1, 2, 1, -1}, {-1, 1, -1, 5}};
  auto b = std::vector<double>{1, 1, 1, 7};
  auto x_expected =
      std::vector<double>{-1.5, 1.71428571, -0.214285714, 0.714285714};
  auto solver = math::LinearSolverLR{A};
  auto x = solver.Solve(b);
  for (std::size_t i = 0; i < x.size(); i++) {
    ASSERT_NEAR(x[i], x_expected[i], EPS);
  }
}

TEST(LinearSystemsTests, LR4) {
  constexpr double EPS = 1e-5;
  auto A = std::vector<std::vector<double>>{
      {-3, 4, -1, 3}, {12, -18, 0, -12}, {0, -8, -19, -2}, {9, -14, 14, 4}};
  auto b = std::vector<double>{1, 1, 1, 7};
  auto x_expected =
      std::vector<double>{-112.666667, -55.166667, 26.333333, -30};
  auto solver = math::LinearSolverLR{A};
  auto x = solver.Solve(b);
  for (std::size_t i = 0; i < x.size(); i++) {
    ASSERT_NEAR(x[i], x_expected[i], EPS);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
