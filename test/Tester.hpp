#ifndef TESTER_HPP
#define TESTER_HPP

#include "Algorithms/LinearSystemsTests.hpp"

#include "../src/Constants.hpp"

#include <map>
#include <functional>
#include <string>
#include <vector>
#include <iostream>

class Tester {

  std::map<std::string, std::function<bool()>> tests;

public:
  Tester();

  bool run();

private:

  template <typename T>
  static std::map<std::string, std::function<bool()>> createTests();
};

template <typename T>
std::map<std::string, std::function<bool()>> Tester::createTests() {

  std::map<std::string, std::function<bool()>> ret;
  T testGroup;
  for (auto& test : testGroup.tests) {
    auto& testName = std::get<0>(test);
    auto& testInput = std:: get<1>(test);
    auto& testSize = std::get<2>(test);
    auto& testSolution = std::get<3>(test);

    stringstream solutionStream(testSolution);
    vector<double> correctSolution;
    {
      double x;
      while (solutionStream >> x) {
        correctSolution.push_back(x);
      }
    }
    auto testPredicate = [correctSolution, testInput, testSize]()->bool {
      vector<double> solution = T::solve(testInput, testSize);

      if (solution.size() != correctSolution.size()) {
        std::cout << " [Solutions are of different sizes] ";
        return false;
      }

      for (int i = 0; i < (int)solution.size(); i++) {
        if (abs(solution[i] - correctSolution[i]) > T::EPSILON) {
          std::cout << " [Solution wrong at: " << solution[i] << " instead of " << correctSolution[i] << "] ";
          return false;
        }
      }
      return true;
    };
    ret[testName] = testPredicate;
  }
  return ret;
}

#endif
