#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "../Engine/Constants.hpp"
#include "../Core/InputManager.hpp"
#include "../Core/View.hpp"

#include <cstdlib>

enum State {
	WELCOME = 1,
	TUTORIAL = 2,
	MAIN_WINDOW = 3,
	GRAM_SCHMIDT = 4,
	DISTANCE_FROM_SUBSPACE = 5,
	LINEAR_SYSTEM = 6,
	QUIT = 7,
	STATE_NUM = 8
};

class StateMachine {
public:
	StateMachine();

	void setState(State newState) {
		if (newState == State::QUIT)
			exit(0);
		currentState = newState;
		currentScene = scenePtr[newState];
	}

	void showScene() {
		State newState = (*currentScene)();
		setState(newState);
	}

private:
	State currentState;
	View* scenePtr[State::STATE_NUM];
	View* currentScene;

	InputManager input;

	WelcomeView welcome;
	TutorialView tutorial;
	MainMenuView mainMenu;
	GramSchmidtView gramSchmidt;
	DistanceFromSubspaceView distanceFromSubspace;
	LinearSystemView linearSystem;

	//	only one instance
	StateMachine(const StateMachine&);
	StateMachine(const StateMachine&&);
	StateMachine& operator =(const StateMachine&) {}
	StateMachine& operator =(const StateMachine&&) {}
};

#endif
