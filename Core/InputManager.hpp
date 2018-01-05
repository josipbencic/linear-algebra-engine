#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "../Engine/Constants.hpp"
#include "../Engine/AlgebraicStructures/RealCoordinateSpace.hpp"
#include "../Engine/AlgebraicStructures/Polynomial.hpp"
#include "../Engine/AlgebraicStructures/Mat3.hpp"

#include "../Engine/MathStreams.hpp"

#include <vector>

//  Handles input
class InputManager {
public:
  InputManager() = default;

  int processInput(const char* fileName, math::ESpaces space);

  std::vector<math::Rn<3>> space3;
  std::vector<math::Rn<4>> space4;
  std::vector<math::Rn<5>> space5;
  std::vector<math::Polynomial<2>>      spacePoly2;
  std::vector<math::Polynomial<3>>      spacePoly3;
  std::vector<math::Polynomial<4>>      spacePoly4;
  std::vector<math::mat3>           matrixSpace3;
  std::vector<std::vector<double>>      linearSystem;

private:

  //  No copying allowed
  InputManager(const InputManager&&);
  InputManager(const InputManager&);
  InputManager& operator =(const InputManager&&) {}
  InputManager& operator =(const InputManager&) {}
};

#endif
