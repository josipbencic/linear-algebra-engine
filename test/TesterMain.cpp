#include "../src/Algorithms/GramSchmidt.hpp"
#include "../src/Algorithms/LinearSystems.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <tuple>
#include <algorithm>
#include <sstream>
#include <functional>
using namespace std;
using namespace math;

/*/
using TestType = tuple<string, EApplicationState, math::ESpaces>;


namespace TestTypeTraits {

  template <typename VectorType>
  struct DistanceFromSubspaceTraits {

  };

  template <typename VectorType>
  struct GramSchmidtTraits {
  };

  struct LinearSystemTraits {
    static void solve(stringstream& in, stringstream& out) {
      vector<vector<double>> A;
      InputUtil::readLinearSystemFromStream(A, in);

      auto sol = math::GaussianElimination(A);
      auto* s = dynamic_cast<ostream*>(&out);
      OutputUtil::writeLinearSystemSolutionToStream(sol, s);
    }
  };
}

const vector<TestType> tests = {
  make_tuple("DistanceFromSubspaceMat3", EApplicationState::DISTANCE_FROM_SUBSPACE, math::ESpaces::M33),
  make_tuple("GramSchmidtR4", EApplicationState::GRAM_SCHMIDT, math::ESpaces::R4),
  make_tuple("LinearSystem_1", EApplicationState::LINEAR_SYSTEM, math::ESpaces::LINEARSYSTEM),
};

void solveLinearSystem(TestType test, stringstream& in, stringstream& out) {
  TestTypeTraits::LinearSystemTraits::solve(in, out);
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

*/

#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

#include "../src/Algorithms/LinearSystems.hpp"
#include "../src/Algorithms/Interpolation.hpp"
#include "../src/MathStreams.hpp"
using namespace math;

/*
void testLRWithKnownLR() {
  vector<vector<double>> L = { { 1,0,0 },{ 2,1,0 },{ -3,1,1 } };
  vector<vector<double>> R = { { 2,-1,-1 },{ 0,1,2 },{ 0,0,3 } };

  LinearSolverLR solver(L, R);

  auto v = solver.Solve({ -2, -7, -3 });
  for (auto x : v) {
    cout << x << " ";
  }
  cout << endl;
}
*/


using mat = vector<vector<double>>;
ostream& operator <<(ostream& stream, const mat& X) {
  OutputUtil::printMatrixScientific(X, stream);
  return stream;
}

int main() {
  //  stringstream ss("1 -1 2 0 1 -2 1 3 3 -1 0 1 0 1 3 1");
  /*
  stringstream ss("8 6 10 -4 4 2 2 -7 -4 1 2 3 2 3 7 7");
  vector<vector<double>> v(4, vector<double>(4, 0));
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      double x; ss >> x;
      v[i][j] = x;
    }

  LinearSolverLR solver(v);
  OutputUtil::printMatrixScientific(solver.LR, cout);
  auto x = solver.Solve({ -30, 1, -20, 7 });
  for (auto& z : x) {
    cout << z << " ";
  }
  cout << endl;
  */

  /*
  // LR

  //stringstream ss("1 -1 0 1 -1 3 -1 2 2 -4 0 6 1 3 -1 3");
  stringstream ss("-3 4 -1 3 12 -18	0 -12 0 -8 -19 -2 9 -14 14 4");
  mat m(4, vector<double>(4, 0.0));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ss >> m[i][j];
    }
  }
  LinearSolverLR sol(m);
  mat L(4, vector<double>(4, 0.0));
  mat R(4, vector<double>(4, 0.0));
  for (int i = 0; i < 4; i++) {
    L[i][i] = 1.0;
    for (int j = 0; j < i; j++) {
      L[i][j] = sol.LR[i][j];
    }
    for (int j = i; j < 4; j++) {
      R[i][j] = sol.LR[i][j];
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%g ", L[i][j]);
    }
    cout << endl;
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%g ", R[i][j]);
    }
    cout << endl;
  }
  */

  /*

    // CHOLESKY
  mat w{
    {4, -2, 14, 6},
  {-2, 17, -23, -3},
  {14, -23, 66, 21},
  {6, -3, 21, 34}
  };
  Cholesky Ch(w);
  cout << Ch.R << endl;;


  string str =
    "2 -1 0 0 0 -1 2 -1 0 0 0 -1 2 -1 0 0 0 -1 2 -1 0 0 0 -1 2";
  stringstream ss(str);
  mat X(5, vector<double>(5, 0.0));
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++)
      ss >> X[i][j];
  }
  Cholesky Ch2(X);
  cout << Ch2.R << endl;
  */

  //string str2 = "9 0 0 3 0 16 8 -4  0 8 13 -2 3 -4 -2 18";
  string str2 = "16 4 -8 0 4 26 -2 -10 -8 -2 24 -12 0 -10 -12 29";
  stringstream ss2(str2);
  mat X2(4, vector<double>(4, 0.0));
  for (auto& r : X2) {
    for (auto& x : r) {
      ss2 >> x;
    }
  }
  Cholesky Ch3(X2);
  cout << Ch3.R << endl;
/*
  
  //  IP
    */

  /*
  stringstream ss("0 -3 1 -4 2 -7 4 -115 5 -268");
  vector<pair<double, double>> v;
  for (int i = 0; i < 5; i++) {
    double x, y; ss >> x >> y;
    v.push_back({x, y});
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
  */
  getchar();
}
