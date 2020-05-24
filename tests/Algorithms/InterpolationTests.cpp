#include "../../src/Algorithms/Interpolation.hpp"

#include <gtest/gtest.h>

#include <utility>
#include <vector>

TEST(InterpolationTests, Lagrange1) {
  std::vector<std::pair<double, double>> points = {
      {0, -3}, {1, -4}, {2, -7}, {4, -115}, {5, -268}};
  double x = 1;
  math::LagrangeIP lagrange(points);
  ASSERT_DOUBLE_EQ(-4.0, lagrange(x));
}

TEST(InterpolationTests, Newton1) {
  std::vector<std::pair<double, double>> points = {
      {0, -3}, {1, -4}, {2, -7}, {4, -115}, {5, -268}};
  double x = 15;
  math::NewtonIP newtonIP(points);
  ASSERT_DOUBLE_EQ(-11148.0, newtonIP(x));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
