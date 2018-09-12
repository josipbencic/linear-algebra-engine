#ifndef INTERPOLATION_TESTS_HPP
#define INTERPOLATION_TESTS_HPP

#include <vector>
#include <string>
#include <tuple>

#include "../../src/Algorithms/Interpolation.hpp"

struct LagrangeIPTests {
    static constexpr double EPSILON = 1e-5;

    //  Test name, pairs of evaulations points with their values and the evaluation query point,
    //  Number of points, value of polynomial in the evaulation point
    const std::vector<std::tuple<std::string, std::string, int, std::string>>
      tests = {
        { "Lagrange1",
          "0 -3 1 -4 2 -7 4 -115 5 -268 1",
          5,
          "-4"
        },
    };

    static std::vector<double> solve(const std::string& input, int size);
};

struct NewtonIPTests {
  static constexpr double EPSILON = 1e-5;

  //  Test name, pairs of evaulations points with their values and the evaluation query point,
  //  Number of points, value of polynomial in the evaulation point
  const std::vector<std::tuple<std::string, std::string, int, std::string>>
    tests = {
      { "Newton1",
        "0 -3 1 -4 2 -7 4 -115 5 -268 15",
        5,
        "-11148"
      }
  };

  static std::vector<double> solve(const std::string& input, int size);
};

#endif
