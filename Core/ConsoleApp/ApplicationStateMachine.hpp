#ifndef APPLICATION_STATE_MACHINE_HPP
#define APPLICATION_STATE_MACHINE_HPP

#include "ApplicationInputManager.hpp"
#include "ApplicationState.hpp"

#include "../../Engine/Constants.hpp"

#include <cstdlib>

enum class EApplicationState {
  WELCOME = 1,
  TUTORIAL = 2,
  MAIN_WINDOW = 3,
  GRAM_SCHMIDT = 4,
  DISTANCE_FROM_SUBSPACE = 5,
  LINEAR_SYSTEM = 6,
  QUIT = 7,
  STATE_NUM = 8
};

class ApplicationStateMachine {
public:
  ApplicationStateMachine();

  void setState(EApplicationState newState) {
    if (newState == EApplicationState::QUIT)
      exit(0);
    currentState = newState;
    currentScene = scenePtr[static_cast<unsigned>(newState)];
  }

  void showScene(); 


  //  only one instance
  ApplicationStateMachine(const ApplicationStateMachine&) = delete;
  ApplicationStateMachine(const ApplicationStateMachine&&) = delete;
  ApplicationStateMachine& operator =(const ApplicationStateMachine&) = delete;
  ApplicationStateMachine& operator =(const ApplicationStateMachine&&) = delete;

private:
  EApplicationState currentState;
  ApplicationState* scenePtr[static_cast<unsigned>(EApplicationState::STATE_NUM)];
  ApplicationState* currentScene;

  InputManager input;

  WelcomeState welcome;
  TutorialState tutorial;
  MainMenuState mainMenu;
  GramSchmidtState gramSchmidt;
  DistanceFromSubspaceState distanceFromSubspace;
  LinearSystemState linearSystem;
};

#endif
