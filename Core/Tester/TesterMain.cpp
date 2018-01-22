#ifndef TESTER
#define TESTER 1
#endif
#if TESTER > 0

#include "../MathStreams.hpp"
#include "../ConsoleApp/ApplicationStateMachine.hpp"

#include "../../Engine/Algorithms/GramSchmidt.hpp"
#include "../../Engine/Algorithms/GaussianElimination.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <tuple>
#include <algorithm>
#include <sstream>
using namespace std;
using namespace math;

using TestType = tuple<string, EApplicationState, math::ESpaces>;

const vector<TestType> tests = {
  make_tuple( "DistanceFromSubspaceMat3", EApplicationState::DISTANCE_FROM_SUBSPACE, math::ESpaces::M33),
  make_tuple("GramSchmidtR4", EApplicationState::GRAM_SCHMIDT, math::ESpaces::R4),
  make_tuple("LinearSystem_1", EApplicationState::LINEAR_SYSTEM, math::ESpaces::LINEARSYSTEM),
};


void solveLinearSystem(TestType test, stringstream& in, stringstream& out) {
  vector<vector<double>> A;
  InputUtil::readLinearSystemFromStream(A, in);

  auto sol = math::GaussianElimination(A);
  auto* s = dynamic_cast<ostream*>(&out);
  OutputUtil::writeLinearSystemSolutionToStream(sol, s);
}

template <typename VectorSpace>
void solveGSorDistInSpace(TestType test, stringstream& in, stringstream& out) {
  vector<VectorSpace> space;
  InputUtil::readVectorSpaceInputFromStream(space, in);
  auto* s = dynamic_cast<ostream*>(&out);
  if (get<1>(test) == EApplicationState::DISTANCE_FROM_SUBSPACE) {
    OutputUtil::writeDistanceFromSubspaceSolutionToStream(space, s);
  }
  else {
    OutputUtil::writeGramSchmidtSolutionToStream(space, s);
  }
}

string solveTest(TestType test, ifstream& fromName) {
  stringstream in;
  stringstream sol;
  in << fromName.rdbuf();

  if (get<1>(test) == EApplicationState::LINEAR_SYSTEM) {
    solveLinearSystem(test, in, sol);
    return sol.str();
  }

  switch (get<2>(test)) {
  case math::ESpaces::R3:
    solveGSorDistInSpace<Rn<3>>(test, in, sol);
    break;
  case math::ESpaces::R4:
    solveGSorDistInSpace<Rn<4>>(test, in, sol);
    break;
  case math::ESpaces::R5:
    solveGSorDistInSpace<Rn<5>>(test, in, sol);
    break;
  case math::ESpaces::M33:
    solveGSorDistInSpace<M33>(test, in, sol);
    break;
  }
  return sol.str();
}


bool checkValidity(TestType test, string& sol) {

  auto name = get<0>(test);
  auto solutionLocation = string("Input/Tests/Solutions/") + name + string(".txt");

  ifstream correctSolutionFile(solutionLocation);
  if (!correctSolutionFile.is_open()) {
    cout << (string("Failed to open ") + solutionLocation + string(" solution!")) << endl;
    return false;
  }

  string correctSolution;
  string str;
  while (getline(correctSolutionFile, str)) {
    correctSolution += str;
    str.clear();
  }

  auto to_remove = [](char x) -> bool {
    return x == '\n' || x == ' ' || x == '\t';
  };

  correctSolution.erase(
    remove_if(begin(correctSolution), end(correctSolution), to_remove),
    end(correctSolution)
  );
  sol.erase(
    remove_if(begin(sol), end(sol), to_remove),
    end(sol)
  );


  return correctSolution == sol;
}


int main() {
  cout << "Starting the algorithm tester..." << endl;
  for (auto& test : tests) {

    auto name = get<0>(test);
    auto state = get<1>(test);

    cout << "Performing test " << name;

    auto problemLocation = string("Input/Tests/") + name + string(".txt");

    ifstream from(problemLocation);
    if (!from.is_open()) {
      cout << "Couldn't open " << problemLocation << endl;
      continue;
    }

    auto sol = solveTest(test, from);
    bool success = checkValidity(test, sol);
    if (success) {
      cout << " -> Passed." << endl;
    }
    else {
      cout << " -> Failed!" << endl;
    }
  }

  getchar();
}
#endif
