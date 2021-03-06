#ifndef INCLUDED_APPLICATION_INPUT_MANAGER_HPP
#define INCLUDED_APPLICATION_INPUT_MANAGER_HPP

#include "../src/MathStreams.hpp"
#include "../src/Constants.hpp"
#include "../src/AlgebraicStructures/RealCoordinateSpace.hpp"
#include "../src/AlgebraicStructures/Polynomial.hpp"
#include "../src/AlgebraicStructures/Mat3.hpp"

#include <vector>
#include <string>

class InputManager {
public:
  InputManager() = default;

  int processInput(std::string filePath, math::ESpaces space);

  inline bool empty() const {
    return space3.empty() && space4.empty() && space5.empty() && spacePoly2.empty()
      && spacePoly3.empty() && spacePoly4.empty() && matrixSpace3.empty() && linearSystem.empty();
  }

  inline math::ESpaces space() const {
    if (!space3.empty()) {
      return math::ESpaces::R3;
    }
    if (!space4.empty()) {
      return math::ESpaces::R4;
    }
    if (!space5.empty()) {
      return math::ESpaces::R5;
    }
    if (!spacePoly2.empty()) {
      return math::ESpaces::POLY2;
    }
    if (!spacePoly3.empty()) {
      return math::ESpaces::POLY3;
    }
    if (!spacePoly4.empty()) {
      return math::ESpaces::POLY4;
    }
    if (!matrixSpace3.empty()) {
      return math::ESpaces::M33;
    }
    return math::ESpaces::LINEARSYSTEM;
  }

  //  No copying allowed
  InputManager(const InputManager&&) = delete;
  InputManager(const InputManager&) = delete;
  InputManager& operator =(const InputManager&&) = delete;
  InputManager& operator =(const InputManager&) = delete;

  std::vector<math::Rn<3>> space3;
  std::vector<math::Rn<4>> space4;
  std::vector<math::Rn<5>> space5;
  std::vector<math::Polynomial<2>>      spacePoly2;
  std::vector<math::Polynomial<3>>      spacePoly3;
  std::vector<math::Polynomial<4>>      spacePoly4;
  std::vector<math::M33>               matrixSpace3;
  std::vector<std::vector<double>>      linearSystem;
};

#endif
