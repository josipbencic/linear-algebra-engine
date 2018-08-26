#ifndef TESTER_HPP
#define TESTER_HPP

#include "Algorithms/LinearSystemsTests.hpp"

#include "../src/Constants.hpp"

#include <map>
#include <functional>
#include <string>
#include <vector>

class Tester {

  std::map<std::string, std::function<bool()>> tests;

public:
  Tester();

  bool run();

private:

  template <typename T>
  std::map<std::string, std::function<bool()>> createTests();

  std::vector<double> parseFileToNumbers(const std::string& fileName);
};

template <typename T>
std::map<std::string, std::function<bool()>> Tester::createTests() {

  std::map<std::string, std::function<bool()>> ret;
  T testGroup;
  for (auto& test : testGroup.tests) {
    auto& testName = get<0>(test);
    auto& testData = get<1>(test);
    auto& testSize = get<2>(test);
    auto& testSolution = get<3>(test);

    stringstream solutionStream(testSolution);
    vector<double> correctSolution(testSize * testSize);
    for (auto& x : correctSolution) {
      solutionStream >> x;
    }

    auto testPredicate = [correctSolution, testData, testSize]()->bool {
      T::Solver solver{ T::transformInput(testData, testSize) };
      T::solve(solver);
      vector<double> solution = T::transformSolution(solver);

      auto iter = mismatch(
        begin(solution), end(solution), begin(correctSolution), end(correctSolution),
        [](double a, double b) -> bool {
          return abs(a - b) > math::EPSILON;
       });

      return iter.first != end(solution) || iter.second != end(correctSolution);
    };
    ret[testName] = testPredicate;
  }
  return ret;
}

#endif
