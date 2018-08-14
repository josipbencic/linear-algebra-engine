#include "ApplicationInputManager.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using namespace math;

int InputManager::processInput(string filePath, ESpaces space) {

  ifstream file(filePath);
  if (!file.is_open()) {
    cout << "Failed to open file " << filePath << endl;
    return 1;
  }

  stringstream stream;
  stream << file.rdbuf();
  file.close();

  switch (space) {
  case ESpaces::R3:
    return InputUtil::readVectorSpaceInputFromStream(space3, stream);
  case ESpaces::R4:
    return InputUtil::readVectorSpaceInputFromStream(space4, stream);
  case ESpaces::R5:
    return InputUtil::readVectorSpaceInputFromStream(space5, stream);
  case ESpaces::M33:
    return InputUtil::readVectorSpaceInputFromStream(matrixSpace3, stream);
  case ESpaces::LINEARSYSTEM:
    return InputUtil::readLinearSystemFromStream(linearSystem, stream);
  }
  return 1;
}
