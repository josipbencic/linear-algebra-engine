#include "ApplicationStateMachine.hpp"

#include "../../Core/Platform.hpp"

using namespace std;

ApplicationStateMachine::ApplicationStateMachine()
  : currentState(EApplicationState::WELCOME)
  , input()
  , welcome()
  , tutorial()
  , mainMenu()
  , gramSchmidt(input)
  , distanceFromSubspace(input)
  , linearSystem(input) {

  scenePtr[static_cast<unsigned>(EApplicationState::WELCOME)] = &welcome;
  scenePtr[static_cast<unsigned>(EApplicationState::TUTORIAL)] = &tutorial;
  scenePtr[static_cast<unsigned>(EApplicationState::MAIN_WINDOW)] = &mainMenu;
  scenePtr[static_cast<unsigned>(EApplicationState::GRAM_SCHMIDT)] = &gramSchmidt;
  scenePtr[static_cast<unsigned>(EApplicationState::DISTANCE_FROM_SUBSPACE)] = &distanceFromSubspace;
  scenePtr[static_cast<unsigned>(EApplicationState::LINEAR_SYSTEM)] = &linearSystem;

  currentScene = &welcome;
}


void ApplicationStateMachine::showScene() {
  system(CLEAR);
  ostream* stream = &cout;
  EApplicationState newState = (*currentScene)(stream);
  setState(newState);
}