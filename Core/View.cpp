#include "View.hpp"

#include "../Core/Platform.hpp"
#include "../Core/StateMachine.hpp"
#include "../Core/InputManager.hpp"

#include "../Engine/Constants.hpp"
#include "../Engine/Algorithms/GramSchmidt.hpp"
#include "../Engine/Algorithms/GaussianElimination.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;


State WelcomeView::operator ()() {

	system(CLEAR);
	cout << "\n\n\tThis is a Linear Algebra Engine\n\n\n";
	cout << "\tPress enter to continue...\n\t" << flush;
	getchar();
	return State::MAIN_WINDOW;
}

State TutorialView::operator ()() {

	system(CLEAR);
	cout << "\n\t INPUT TUTORIAL \n\n";
	cout << "\t This program operates through files.\n"
		<< "\t Name your file input.txt and place it in the Input folder.\n\n";
	cout << "\tFile has to contain:\n";
	cout << "\t\t Number of vectors you will operate with\n";
	cout << "\t\t Given vectors, each in its own line\n"
		<< "\t\t (matrices are entered row by row in the same line)\n\n";
	cout << "\t Note: For distance from subspace algorithm, enter an additional\n"
		<< " \t vector at the end (also remember to count it in.)\n";
	cout << "\t Note2: Polynomial Inner Product is defined cannoicaly.\n";
	cout << "\t\t Polynomials are typed as coefficients, from highest to lowest powers.\n";
	cout << "\t\t Empty powers are inputted as 0.\n";
	cout << "\n\n\tPress any key to return to the Main menu.\n\n";
	getchar(); getchar();
	return State::MAIN_WINDOW;
}

State MainMenuView::operator ()() {

	system(CLEAR);
	cout << "\n\n\t Choose what you want to do (select a number):\n\n";
	cout << "\t(1)\t Input tutorial\n";
	cout << "\t(2)\t Gram Schmidt Orthogonalization algorithm\n";
	cout << "\t(3)\t Distance From Subspace Calculator\n";
	cout << "\t(4)\t System of Linear Equations\n";
	cout << "\t(0)\t Quit\n" << flush;

	char ans = getchar();
	while (ans < '0' || ans > '4') ans = getchar();
	ans -= '0';

	if (ans == 1) return State::TUTORIAL;
	if (ans == 2) return State::GRAM_SCHMIDT;
	if (ans == 3) return State::DISTANCE_FROM_SUBSPACE;
	if (ans == 4) return State::LINEAR_SYSTEM;
	if (ans == 0) return State::QUIT;

	return State::MAIN_WINDOW;
}

//	wrapper function
inline math::Spaces selectSpace() {

	cout << "\tSelect the space on which you want to operate:\n";
	cout << "\t(0) R3\n";
	cout << "\t(1) R4\n";
	cout << "\t(2) R5\n";
	cout << "\t(3) Polynomials of 2nd degree.\n";
	cout << "\t(4) Polynomials of 3rd degree.\n";
	cout << "\t(5) Polynomials of 4th degree.\n";
	cout << "\t(6) M3 over Reals\n\n";
	cout << "\t" << flush;

	char spaceNum = getchar();
	while (spaceNum < '0' || spaceNum > '6')
		spaceNum = getchar();
	spaceNum -= '0';
	math::Spaces space = static_cast<math::Spaces>(spaceNum);
	return space;
}

//	helper function to handle all spaces
template<typename VectorSpace>
void outputGramSchmidt(std::vector<VectorSpace>& v) {

	cout << "\n\t The result:\n\n";
	std::vector<VectorSpace> ret = math::GramSchmidt(v);
	for (unsigned i = 0; i < ret.size(); i++)
		cout << "\t" << ret[i] << "\n";
	cout << flush;
}

State GramSchmidtView::operator ()() {

	system(CLEAR);
	cout << "\n\n\tGRAM-SCHMIDT ORTHOGONALIZATION ALGORITHM\n\n";

	math::Spaces space = selectSpace();

	cout << "\t Enter the name of the file in which your input is.\n";
	cout << "\t NOTE: Make sure the file is inside the Input folder\n";
	cout << "\n\t" << flush;

	string fileName; cin >> fileName;
	if (input.processInput(fileName.c_str(), space)) {
		cout << "\tThere was an error in the specified file.\n";
		cout << "\tPress any key to return to the Main Window...\n";
		cout << "\n\t" << flush;
		getchar(); getchar();
		return State::MAIN_WINDOW;
	}

	switch (space) {
	case math::Spaces::SPACE3:
		outputGramSchmidt(input.space3);
		break;
	case math::Spaces::SPACE4:
		outputGramSchmidt(input.space4);
		break;
	case math::Spaces::SPACE5:
		outputGramSchmidt(input.space5);
		break;
	case math::Spaces::MATRIXSPACE3:
		outputGramSchmidt(input.matrixSpace3);
		break;
	}

	getchar(); getchar();
	return State::MAIN_WINDOW;
}

//	analogous helper function
template <typename VectorSpace>
void outputDistanceFromSubspace(std::vector<VectorSpace>& linearHull) {

	VectorSpace v = linearHull[linearHull.size() - 1];
	linearHull.pop_back();
	double distance = distanceFromSpace(linearHull, v);
	cout << "\n\t The distance is:\n\n";
	cout << distance << endl;
}

State DistanceFromSubspaceView::operator ()() {

	system(CLEAR);
	cout << "\n\n\t DISTANCE FROM SUBSPACE CALCULATOR\n\n";

	math::Spaces space = selectSpace();

	cout << "\t Enter the name of the file in which your input is.\n";
	cout << "\t NOTE: Make sure the file is inside the Input folder\n";
	cout << "\t NOTE: Input needs to be in following order:\n";
	cout << "\t First number of vectors (n), then n-1 vectors that span the subspace";
	cout << "\t and one vector whose distance from subspace you're requesting.\n";
	cout << "\n\t" << flush;

	string fileName; cin >> fileName;
	input.processInput(fileName.c_str(), space);

	switch (space) {
	case math::Spaces::SPACE3:
		outputDistanceFromSubspace(input.space3);
		break;
	case math::Spaces::SPACE4:
		outputDistanceFromSubspace(input.space4);
		break;
	case math::Spaces::SPACE5:
		outputDistanceFromSubspace(input.space5);
		break;
	case math::Spaces::MATRIXSPACE3:
		outputDistanceFromSubspace(input.matrixSpace3);
		break;
	}
	getchar(); getchar();
	return State::MAIN_WINDOW;
}

State LinearSystemView::operator ()() {

	system(CLEAR);
	cout << "\n\n\t LINEAR SYSTEM SOLVER\n\n";
	cout << "\t Enter the name of the file in which your input is.\n";
	cout << "\t NOTE: Make sure the file is inside the Input folder\n";
	cout << "\t NOTE: Input formatting. Given a linear system:\n\n";
	cout << "\t\t a11 * x1 + a12 * x2 + ... + a1n * xn = b1\n\t\t\t(...)\n";
	cout << "\t\t an1 * x1 + an2 * x2 + ... + ann * xn = bn\n\n";
	cout << "\t Type it in the following order:\n\n";
	cout << "\t\t n\n";
	cout << "\t\t a11 a12 ... a1n b1\n\t\t\t(...)\n\t\t an1 an2 ... ann bn\n";
	cout << "\n\t" << flush;

	string fileName; cin >> fileName;
	input.processInput(fileName.c_str(), math::Spaces::LINEARSYSTEM);

	std::vector<double> ret = math::GaussianElimination(input.linearSystem);
	cout << "\t The result:\n\n";
	for (unsigned i = 0; i < ret.size(); i++)
		cout << "\tx" << (i + 1) << " = " << ret[i] << "\n";
	cout << endl;

	getchar(); getchar();
	return State::MAIN_WINDOW;
}
