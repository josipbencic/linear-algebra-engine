#ifndef LINEAR_SYSTEMS_TESTS_HPP
#define LINEAR_SYSTEMS_TESTS_HPP

#include <string>
#include <functional>
#include <vector>
#include <tuple>
#include <string>

#include "../../src/Algorithms/LinearSystems.hpp"


//{ "Cholesky1",
//  "16 4 -8 0 4 26 -2 -10 -8 -2 24 -12 0 -10 -12 29",
//  4,
//  ""
//},

struct CholeskyTests {

  using Solver = math::Cholesky;

  static constexpr double EPSILON = 1e-5;

  //  Test Name, Matrix, Matrix dimension, Solution Matrix
  const std::vector<std::tuple<std::string, std::string, int, std::string>> tests = {
    { "Cholesky1",
      "9 0 0 3 0 16 8 -4 0 8 13 -2 3 -4 -2 18",
      4,
      "3 0 0 1 0 4 2 -1 0 0 3 0 0 0 0 4"
    },
    { "Cholesky2",
      "4 -2 14 6 -2 17 -23 -3 14 -23 66 21 6 -3 21 34",
      4,
      "2 -1 7 3 0 4 -4 0 0 0 1 0 0 0 0 5"
    }
    //{ "Cholesky3",
    //  "2 -1 0 0 0 -1 2 -1 0 0 0 -1 2 -1 0 0 0 -1 2 -1 0 0 0 -1 2",
    //  5,
    //  "+1.414214 -0.707107 +0.000000 +0.000000 +0.000000" \
    //  "+0.000000 +1.224745 -0.816497 +0.000000 +0.000000" \
    //  "+0.000000 +0.000000 +1.154701 -0.866025 +0.000000" \
    //  "+0.000000 +0.000000 +0.000000 +1.118034 -0.894427" \
    //  "+0.000000 +0.000000 +0.000000 +0.000000 +1.095445"
    //}
  };

  static std::vector<double> solve(const std::string& input, int size);
};

//    TODO: Write these tests and integrate them in the Tester.
struct LinearSolverLRTests {

  using Solver = math::LinearSolverLR;

  static constexpr double EPSILON = 1e-5;

  //  Test Name, Matrix and test vector, Matrix dimension, Solution Matrix
  const std::vector<std::tuple<std::string, std::string, unsigned, std::string>>
    tests = {
    { "LRSolving1",
      "1 1 5 4 2 1 6 3 1 " "1 1 7",
      3,
      "-50 106 -11"
    },
    { "LRSolving2",
      "1 -1 0 1 -1 3 -1 2 2 -4 0 6 1 3 -1 3 " "1 1 1 7",
      4,
      "2.5 2.5 6 1"
    },
    { "LRSolving3",
      "0 0 2 2 2 2 4 2 1 2 1 -1 -1 1 -1 5 " "1 1 1 7",
      4,
      "-1.5 1.71428571 -0.214285714 0.714285714"
    },
    { "LRSolving4",
      "-3 4 -1 3 12 -18 0 -12 0 -8 -19 -2 9 -14 14 4 " "1 1 1 7",
      4,
      "-112.666667 -55.166667 26.333333 -30"
    },
    { "LRSolving5",
      "8 6 10 -4 4 2 2 -7 -4 1 2 3 2 3 7 7 " "-30 1 -20 7",
      4,
      "37.1 494.2 -298.4 77"
    },
    { "LRSolving6",
      "1 -1 2 0 1 -2 1 3 3 -1 0 1 0 1 3 1 " "-30 1 -20 7",
      4,
      "-6.86956522 11.7391304 -5.69565217 12.3478261"
    },
    { "LRSolving7",
      "1 -1 2 0 1 -2 1 3 3 -1 0 1 0 1 3 1 " "0.1 0.1 0.3333 0",
      4,
      "0.11173913 0.00652173913 -0.00260869565 0.00130434783"
    }
  };

  static std::vector<double> solve(const std::string& input, int size);
};

#endif
