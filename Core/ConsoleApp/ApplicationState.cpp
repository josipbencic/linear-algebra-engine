#include "ApplicationState.hpp"

#include "ApplicationStateMachine.hpp"
#include "ApplicationInputManager.hpp"

#include "../../Core/Platform.hpp"
#include "../../Core/MathStreams.hpp"

#include "../../Engine/Constants.hpp"
#include "../../Engine/Algorithms/GramSchmidt.hpp"
#include "../../Engine/Algorithms/LinearSystems.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

EApplicationState WelcomeState::operator ()(ostream* stream) {
  ostream& out = *stream;
  out << "\n\n\tThis is a Linear Algebra Engine\n\n\n";
  out << "\tPress enter to continue...\n\t" << flush;
  getchar();
  return EApplicationState::MAIN_WINDOW;
}

EApplicationState TutorialState::operator ()(ostream* s) {
  ostream& stream = *s;
  stream << "\n\t INPUT TUTORIAL \n\n";
  stream << "\t This program operates through files.\n"
    << "\t Name your file input.txt and place it in the Input folder.\n\n";
  stream << "\tFile has to contain:\n";
  stream << "\t\t Number of vectors you will operate with\n";
  stream << "\t\t Given vectors, each in its own line\n"
    << "\t\t (matrices are entered row by row in the same line)\n\n";
  stream << "\t Note: For distance from subspace algorithm, enter an additional\n"
    << " \t vector at the end (also remember to count it in.)\n";
  stream << "\t Note2: Polynomial Inner Product is defined canonically.\n";
  stream << "\t\t Polynomials are typed as coefficients, from highest to lowest powers.\n";
  stream << "\t\t Empty powers are inputted as 0.\n";
  stream << "\n\n\tPress any key to return to the Main menu.\n\n";
  getchar(); getchar();
  return EApplicationState::MAIN_WINDOW;
}

EApplicationState MainMenuState::operator ()(ostream* s) {
  ostream& stream = *s;
  stream << "\n\n\t Choose what you want to do (select a number):\n\n";
  stream << "\t(1)\t Input tutorial\n";
  stream << "\t(2)\t Gram Schmidt Orthogonalization algorithm\n";
  stream << "\t(3)\t Distance From Subspace Calculator\n";
  stream << "\t(4)\t System of Linear Equations\n";
  stream << "\t(0)\t Quit\n" << flush;

  int ans = getchar();
  while (ans < '0' || ans > '4') {
    ans = getchar();
  }
  ans -= '0';

  switch (ans) {
    case 1: return EApplicationState::TUTORIAL;
    case 2: return EApplicationState::GRAM_SCHMIDT;
    case 3: return EApplicationState::DISTANCE_FROM_SUBSPACE;
    case 4: return EApplicationState::LINEAR_SYSTEM;
    case 0: return EApplicationState::QUIT;
  }
  return EApplicationState::MAIN_WINDOW;
}

math::ESpaces selectSpace(ostream& stream) {

  stream << "\tSelect the space on which you want to operate:\n";
  stream << "\t(0) R3\n";
  stream << "\t(1) R4\n";
  stream << "\t(2) R5\n";
  stream << "\t(3) Polynomials of 2nd degree.\n";
  stream << "\t(4) Polynomials of 3rd degree.\n";
  stream << "\t(5) Polynomials of 4th degree.\n";
  stream << "\t(6) M3 over Reals\n\n";
  stream << "\t" << flush;

  int spaceNum = getchar();
  while (spaceNum < '0' || spaceNum > '6') {
    spaceNum = getchar();
  }
  spaceNum -= '0';
  math::ESpaces space = static_cast<math::ESpaces>(spaceNum);
  return space;
}


EApplicationState GramSchmidtState::operator ()(ostream* stream) {
  ostream& out = *stream;

  math::ESpaces space;

  if (input.empty()) {

    out << "\n\n\tGRAM-SCHMIDT ORTHOGONALIZATION ALGORITHM\n\n";

    space = selectSpace(out);

    out << "\t Enter the name of the file in which your input is.\n";
    out << "\t NOTE: Make sure the file is inside the Input folder\n";
    out << "\n\t" << flush;

    string fileName; cin >> fileName;
    if (input.processInput(string("Input/") + fileName, space)) {
      out << "\tThere was an error in the specified file.\n";
      out << "\tPress any key to return to the Main Window...\n";
      out << "\n\t" << flush;
      getchar(); getchar();
      return EApplicationState::MAIN_WINDOW;
    }
  }
  else {
    space = input.space();
  }

  switch (space) {
  case math::ESpaces::R3:
    OutputUtil::writeGramSchmidtSolutionToStream(input.space3, stream);
    break;
  case math::ESpaces::R4:
    OutputUtil::writeGramSchmidtSolutionToStream(input.space4, stream);
    break;
  case math::ESpaces::R5:
    OutputUtil::writeGramSchmidtSolutionToStream(input.space5, stream);
    break;
  case math::ESpaces::M33:
    OutputUtil::writeGramSchmidtSolutionToStream(input.matrixSpace3, stream);
    break;
  }

  getchar(); getchar();
  return EApplicationState::MAIN_WINDOW;
}

EApplicationState DistanceFromSubspaceState::operator ()(ostream* stream) {
  ostream& out = *stream;
  out << "\n\n\t DISTANCE FROM SUBSPACE CALCULATOR\n\n";

  math::ESpaces space = selectSpace(out);

  out << "\t Enter the name of the file in which your input is.\n";
  out << "\t NOTE: Make sure the file is inside the Input folder\n";
  out << "\t NOTE: Input needs to be in following order:\n";
  out << "\t First number of vectors (n), then n-1 vectors that span the subspace\n";
  out << "\t and one vector whose distance from subspace you're requesting.\n";
  out << "\n\t" << flush;

  string fileName; cin >> fileName;
  input.processInput(string("Input/") + fileName, space);

  switch (space) {
  case math::ESpaces::R3:
    OutputUtil::writeDistanceFromSubspaceSolutionToStream(input.space3, stream);
    break;
  case math::ESpaces::R4:
    OutputUtil::writeDistanceFromSubspaceSolutionToStream(input.space4, stream);
    break;
  case math::ESpaces::R5:
    OutputUtil::writeDistanceFromSubspaceSolutionToStream(input.space5, stream);
    break;
  case math::ESpaces::M33:
    OutputUtil::writeDistanceFromSubspaceSolutionToStream(input.matrixSpace3, stream);
    break;
  }
  getchar(); getchar();
  return EApplicationState::MAIN_WINDOW;
}

EApplicationState LinearSystemState::operator ()(ostream* stream) {
  ostream& out = *stream;
  out << "\n\n\t LINEAR SYSTEM SOLVER\n\n";
  out << "\t Enter the name of the file in which your input is.\n";
  out << "\t NOTE: Make sure the file is inside the Input folder\n";
  out << "\t NOTE: Input formatting. Given a linear system:\n\n";
  out << "\t\t a11 * x1 + a12 * x2 + ... + a1n * xn = b1\n\t\t\t(...)\n";
  out << "\t\t an1 * x1 + an2 * x2 + ... + ann * xn = bn\n\n";
  out << "\t Type it in the following order:\n\n";
  out << "\t\t n\n";
  out << "\t\t a11 a12 ... a1n b1\n\t\t\t(...)\n\t\t an1 an2 ... ann bn\n";
  out << "\n\t" << flush;

  string fileName; cin >> fileName;
  input.processInput(string("Input/") + fileName, math::ESpaces::LINEARSYSTEM);

  auto ret = math::GaussianElimination(input.linearSystem);
  OutputUtil::writeLinearSystemSolutionToStream(ret, stream);


  getchar(); getchar();
  return EApplicationState::MAIN_WINDOW;
}
