#include "StateMachine.hpp"

#include "../Core/Platform.hpp"

using namespace std;

StateMachine::StateMachine()
	: currentState(State::WELCOME)
	, input()
	, welcome()
	, tutorial()
	, mainMenu()
	, gramSchmidt(input)
	, distanceFromSubspace(input)
	, linearSystem(input) {

	scenePtr[State::WELCOME] = &welcome;
	scenePtr[State::TUTORIAL] = &tutorial;
	scenePtr[State::MAIN_WINDOW] = &mainMenu;
	scenePtr[State::GRAM_SCHMIDT] = &gramSchmidt;
	scenePtr[State::DISTANCE_FROM_SUBSPACE] = &distanceFromSubspace;
	scenePtr[State::LINEAR_SYSTEM] = &linearSystem;

	currentScene = &welcome;
}
